#include "core.h"

AdsManager* g_pAdsManager = 0;

AdsManager::~AdsManager(){
	// Destroy the web view
	if (m_pView){
		s3eWebViewUnRegister(S3E_WEBVIEW_STARTED_LOADING, AdsManager::StartedLoadingCallback, m_pView);
		s3eWebViewUnRegister(S3E_WEBVIEW_FINISHED_LOADING, AdsManager::LoadedCallback, m_pView);
		s3eWebViewUnRegister(S3E_WEBVIEW_FAILED_LOADING, AdsManager::ErrorCallback, m_pView);
		s3eWebViewDestroy(m_pView);
		m_pView = NULL;
	}
}

bool AdsManager::Init(){
	// Check ads are enabled
	if (!IsEnabled())
		return false;

	// Check that the web view extension is available
	if (s3eWebViewAvailable() == S3E_FALSE)
		return false;

	// Create the web view
	m_pView = s3eWebViewCreate(true);
	if (!m_pView)
		return false;

	// Check that the platform is supported
	m_platform = s3eDeviceGetString(S3E_DEVICE_OS);
	if (m_platform != "ANDROID" && m_platform != "IPHONE" && m_platform != "WINDOWS" & m_platform != "OSX")
		return false;

	// Register callbacks
	s3eWebViewRegister(S3E_WEBVIEW_STARTED_LOADING, AdsManager::StartedLoadingCallback, this, m_pView);
	s3eWebViewRegister(S3E_WEBVIEW_FINISHED_LOADING, AdsManager::LoadedCallback, this, m_pView);
	s3eWebViewRegister(S3E_WEBVIEW_FAILED_LOADING, AdsManager::ErrorCallback, this, m_pView);

	return true;
}

bool AdsManager::IsEnabled(){
	// Check storage to see if ads are enabled
	bool enabled = true;
	s3eFile* fh = s3eFileOpen("ads.bin", "rb");
	if (fh != NULL){
		s3eFileRead(&enabled, sizeof(enabled), 1, fh);
		s3eFileClose(fh);
	}

	return enabled;
}

void AdsManager::Disable(){
	// Save ads disabled state to storage
	bool enabled = false;
	s3eFile* fh = s3eFileOpen("ads.bin", "wb");
	if (fh != NULL){
		s3eFileWrite(&enabled, sizeof(enabled), 1, fh);
		s3eFileClose(fh);
	}

	// Destroy the web view
	if (m_pView){
		s3eWebViewUnRegister(S3E_WEBVIEW_STARTED_LOADING, AdsManager::StartedLoadingCallback, m_pView);
		s3eWebViewUnRegister(S3E_WEBVIEW_FINISHED_LOADING, AdsManager::LoadedCallback, m_pView);
		s3eWebViewUnRegister(S3E_WEBVIEW_FAILED_LOADING, AdsManager::ErrorCallback, m_pView);
		s3eWebViewDestroy(m_pView);
		m_pView = NULL;
	}
}

void AdsManager::NavigateAd(const std::string& html){
	// Save the html that will display the ad
	s3eFile* fh = s3eFileOpen("ad_html.html", "wb");
	s3eFileWrite(html.c_str(), html.length(), 1, fh);
	s3eFileClose(fh);

	// Show the web view
	s3eWebViewShow(m_pView, 0, m_y, IwGxGetScreenWidth(), m_h);

	// Navigate to the saved ad html file
	s3eWebViewNavigate(m_pView, "ram://ad_html.html");
}

bool AdsManager::NewInneractiveAd(){
	std::string portal_id = "642";
	if (m_platform == "ANDROID")
		portal_id = "559";
	else if (m_platform != "IPHONE")
		return false;

	// Generate ad html
	std::string html;
	html.reserve(2000);
	html.append("<html><head>");
	html.append("<meta name='viewport' content='width=device-width, initial-scale=1.0, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, user-scalable=no' />");
	html.append("<style> #iaAdContainerDiv { text-align: center; } </style>");
	html.append("</head><body>");
	html.append("<script>");
	html.append("var APP_ID = '");
	html.append(m_id);
	html.append("'; ");
	html.append("var PORTAL = ");
	html.append(portal_id);
	html.append("; ");
	html.append("var CATEGORY = '';");
	html.append("var KEYWORDS = ''; ");
	html.append("var GPS_COORDINATES = ''; ");
	html.append("var LOCATION = ''; ");
	html.append("var IMPRESSION_PIXEL = ''; ");
	html.append("var CLICK_PIXEL = ''; ");
	html.append("var FAILOVER = 'No ad'; ");
	html.append("var IS_MOBILE_WEB = false; ");
	html.append("var IS_ORMMA_SUPPORT = false; ");
	html.append("var IS_MRAID_SUPPORT = false; ");
	if (m_type == kAdType_Wall)
		html.append("var IS_INTERSTITIAL_AD = 'true'; ");
	else
		html.append("var IS_INTERSTITIAL_AD = 'false'; ");
	html.append("document.write(\"<script language='javascript' src='http://ad-tag.inner-active.mobi/simpleM2M/RequestTagAd?v=\" + ((IS_ORMMA_SUPPORT) ? ((IS_MRAID_SUPPORT) ? \"Stag-2.1.0&f=116\" : \"Stag-2.1.0&f=52\") : ((IS_MRAID_SUPPORT) ? \"Stag-2.1.0&f=84\" : \"Stag-2.0.1&f=20\")) + ((IS_INTERSTITIAL_AD) ? \"&fs=true\" : \"&fs=false\") + \"&aid=\" + encodeURIComponent(APP_ID) + \"&po=\" + PORTAL + \"&c=\" + encodeURIComponent(CATEGORY) + \"&k=\" + encodeURIComponent(KEYWORDS) + ((FAILOVER) ? \"&noadstring=\" + encodeURIComponent(FAILOVER) : \"&test=true\") + \"&lg=\" + encodeURIComponent(GPS_COORDINATES) + \"&l=\" + encodeURIComponent(LOCATION) + \"&mw=\" + ((IS_MOBILE_WEB) ? \"true\" : \"false\") + \"'></script>\"); ");
	html.append("</script></body>");
	html.append("</html>");

	NavigateAd(html);

	return true;
}

bool AdsManager::NewLeadboltAd(){
	if (m_type == kAdType_Wall){
		// SHow the web view
		s3eWebViewShow(m_pView, 0, m_y, IwGxGetScreenWidth(), m_h);

		// Navigate to the saved ad html file
		std::string url = "http://ad.leadboltads.net/show_app_wall?section_id=" + m_id;
		s3eWebViewNavigate(m_pView, url.c_str());

		return true;
	}

	// Create html to display ad
	std::string html;
	html.reserve(500);
	html.append("<html><head>");
	html.append("<meta name='viewport' content='width=device-width, initial-scale=1.0, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, user-scalable=no' />");
	html.append("<style> #iaAdContainerDiv { text-align: center; } </style>");
	html.append("</head><body style='margin:0;padding:0;text-align: center;'>");
	html.append("<script src='http://ad.leadboltads.net/show_app_ad.js?section_id=");
	html.append(m_id);
	html.append("'></script>");
	html.append("</body></html>");

	NavigateAd(html);

	return true;
}

bool AdsManager::NewAdmodaAd(){
	if (m_type != kAdType_Banner)
		return false;

	// Create html to display ad
	std::string html;
	html.reserve(500);
	html.append("<html><head>");
	html.append("<meta name='viewport' content='width=device-width, initial-scale=1.0, initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, user-scalable=no' />");
	html.append("<style> #iaAdContainerDiv { text-align: center; } </style>");
	html.append("</head><body style='margin:0;padding:0;text-align: center;'>");
	html.append("<script src='http://www.admoda.com/ads/jsbannertext.php?v=4&l=javascript&z=");
	html.append(m_id);
	html.append("'></script>");
	html.append("</body></html>");

	NavigateAd(html);

	return true;
}

bool AdsManager::NewAd(int y, int height, EAdProviders provider, EAdType type, const char *id){
	if (m_pView == 0)
		return false;

	m_y = y;
	m_h = height;
	m_provider = provider;
	m_type = type;
	m_id = id;

	switch (provider){
		case kAdProvider_Inneractive:
			return NewInneractiveAd();
			break;
		case kAdProvider_Leadbolt:
			return NewLeadboltAd();
			break;
		case kAdProvider_Admoda:
			return NewAdmodaAd();
			break;
	}

	return false;
}


bool AdsManager::NewAd()
{
	if (m_pView == 0)
		return false;

	switch (m_provider){
		case kAdProvider_Inneractive:
			return NewInneractiveAd();
			break;
		case kAdProvider_Leadbolt:
			return NewLeadboltAd();
			break;
		case kAdProvider_Admoda:
			return NewAdmodaAd();
			break;
	}

	return false;
}

int32 AdsManager::LoadedCallback(s3eWebView *pInstance, void *pSystemData, void *pUserData){
	printf("Ad page loaded - %s\n", (char*)pSystemData);
	return 1;
}

int32 AdsManager::ErrorCallback(s3eWebView *pInstance, void *pSystemData, void *pUserData){
	printf("Error loaded ad - %s\n", (char*)pSystemData);
	return 1;
}

int32 AdsManager::StartedLoadingCallback(s3eWebView *pInstance, void *pSystemData, void *pUserData){
	AdsManager* pAds = (AdsManager*)pUserData;
	std::string url = (char*)pSystemData;

	if (pAds->GetProvider() == kAdProvider_Leadbolt && url.find("show_app_ad?") != std::string::npos){
		// Special case for leadbolt that prevents redirects being recognised as an ad click
	}else if (pAds->GetType() == kAdType_Wall){
		// Special case for leadbolt app wall ads, these do not open in a new browser window
	}else{
		if (url.find("http:") != std::string::npos){
			printf("Launching ad with url - %s\n", (char*)pSystemData);
			s3eOSExecExecute(url.c_str(), S3E_FALSE);
			pAds->NewAd();
		}
	}

	return 1;
}
