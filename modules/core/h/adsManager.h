#ifndef __ADS_MANAGER_H__
#define __ADS_MANAGER_H__

class AdsManager
{
public:
	enum EAdProviders{
		kAdProvider_Inneractive = 0,
		kAdProvider_Leadbolt,
		kAdProvider_Admoda,
		
		kAdProvider_Count
	};
	
	enum EAdType{
		kAdType_Banner = 0,
		kAdType_Wall,

		kAdType_Count
	};

protected:
	std::string m_platform;
	std::string m_url;
	s3eWebView* m_pView;
	EAdProviders m_provider;
	EAdType m_type;
	std::string m_id;
	int m_h;
	int m_y;

	void NavigateAd(const std::string& html);
	bool NewInneractiveAd();
	bool NewLeadboltAd();
	bool NewAdmodaAd();

public:
	AdsManager() : m_pView(0) {}
	~AdsManager();

	bool Init();
	void Disable();

	bool NewAd(int y, int height, EAdProviders provider, EAdType type, const char *id);
	bool NewAd();

	EAdProviders GetProvider() const { return m_provider; }
	EAdType GetType() const { return m_type; }
	bool IsEnabled();

	static int32 LoadedCallback(s3eWebView *pInstance, void *pSystemData, void *pUserData);
	static int32 ErrorCallback(s3eWebView *pInstance, void *pSystemData, void *pUserData);
	static int32 StartedLoadingCallback(s3eWebView *pInstance, void *pSystemData, void *pUserData);
};

extern AdsManager* g_pAdsManager;

#endif // __ADS_MANAGER_H__
