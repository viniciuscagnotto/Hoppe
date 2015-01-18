# -*- coding: utf-8 -*-
# Deployment settings for OldMan.
# This file is autogenerated by the mkb system and used by the s3e deployment
# tool during the build process.

config = {}
cmdline = ['C:/Marmalade/7.4.1/s3e/makefile_builder/mkb.py', 'c:/Users/Vinicius/Desktop/Yes or No/OldMan/OldMan.mkb', '--deploy-only', '--hub-data', 'C:/Users/Vinicius/Desktop/Yes or No/OldMan/project_OldMan/mkb-windows.txt', '--buildenv=VC12X']
mkb = 'c:/Users/Vinicius/Desktop/Yes or No/OldMan/OldMan.mkb'
mkf = ['c:\\marmalade\\7.4.1\\s3e\\s3e-default.mkf', 'c:\\marmalade\\7.4.1\\extensions\\s3eiosgamecenter\\s3eiosgamecenter.mkf', 'c:\\marmalade\\7.4.1\\modules\\iwutil\\iwutil.mkf', 'c:\\marmalade\\7.4.1\\modules\\third_party\\libjpeg\\libjpeg.mkf', 'c:\\marmalade\\7.4.1\\modules\\third_party\\libpng\\libpng.mkf', 'c:\\marmalade\\7.4.1\\modules\\third_party\\zlib\\zlib.mkf', 'c:\\marmalade\\7.4.1\\extensions\\s3ewebview\\s3ewebview.mkf', 'c:\\marmalade\\7.4.1\\extensions\\s3efacebook\\s3efacebook.mkf', 'c:\\marmalade\\7.4.1\\modules\\iw2d\\iw2d.mkf', 'c:\\marmalade\\7.4.1\\modules\\iwgx\\iwgx.mkf', 'c:\\marmalade\\7.4.1\\modules\\iwgl\\iwgl.mkf', 'c:\\marmalade\\7.4.1\\modules\\iwgeom\\iwgeom.mkf', 'c:\\marmalade\\7.4.1\\modules\\iwresmanager\\iwresmanager.mkf', 'c:\\marmalade\\7.4.1\\extensions\\pvrtextool\\pvrtextool.mkf', 'c:\\marmalade\\7.4.1\\modules\\iwgxfont\\iwgxfont.mkf', 'c:\\marmalade\\7.4.1\\modules\\third_party\\tiniconv\\tiniconv.mkf', 'c:\\marmalade\\7.4.1\\modules\\iw2dscenegraph\\iw2dscenegraph.mkf', 'c:\\marmalade\\7.4.1\\modules\\iw2dscenegraphcore\\iw2dscenegraphcore.mkf', 'c:\\marmalade\\7.4.1\\modules\\iwtween\\iwtween.mkf', 'c:\\users\\vinicius\\desktop\\yes or no\\oldman\\modules\\soundengine\\soundengine.mkf', 'c:\\marmalade\\7.4.1\\extensions\\s3eflurry\\s3eflurry.mkf', 'c:\\users\\vinicius\\desktop\\yes or no\\oldman\\modules\\core\\core.mkf']

class DeployConfig(object):
    pass

######### ASSET GROUPS #############

assets = {}

assets['Default'] = [
    ('c:/Users/Vinicius/Desktop/Yes or No/OldMan/data/ads', 'ads', 0),
    ('c:/Users/Vinicius/Desktop/Yes or No/OldMan/data/audio', 'audio', 0),
    ('c:/Users/Vinicius/Desktop/Yes or No/OldMan/data/textures', 'textures', 0),
    ('c:/Users/Vinicius/Desktop/Yes or No/OldMan/data/atlas', 'atlas', 0),
    ('c:/Users/Vinicius/Desktop/Yes or No/OldMan/data/icons', 'icons', 0),
    ('c:/Users/Vinicius/Desktop/Yes or No/OldMan/data/splashscreens', 'splashscreens', 0),
    ('c:/Users/Vinicius/Desktop/Yes or No/OldMan/data-ram/data-gles1,c:/Users/Vinicius/Desktop/Yes or No/OldMan/data', '.', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/s3eWebView.js', 's3eWebView.js', 0),
]

assets['WebView32Assets'] = [
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/locales', 'locales', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/avcodec-53.dll', 'avcodec-53.dll', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/avformat-53.dll', 'avformat-53.dll', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/avutil-51.dll', 'avutil-51.dll', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/chrome.pak', 'chrome.pak', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/d3dcompiler_43.dll', 'd3dcompiler_43.dll', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/d3dx9_43.dll', 'd3dx9_43.dll', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/icudt.dll', 'icudt.dll', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/libcef.dll', 'libcef.dll', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/libEGL.dll', 'libEGL.dll', 0),
    ('c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/libGLESv2.dll', 'libGLESv2.dll', 0),
]

######### DEFAULT CONFIG #############

class DefaultConfig(DeployConfig):
    embed_icf = -1
    name = 'OldMan'
    pub_sign_key = 0
    priv_sign_key = 0
    caption = 'OldMan'
    long_caption = 'OldMan'
    version = [0, 0, 1]
    config = ['c:/Users/Vinicius/Desktop/Yes or No/OldMan/data/app.icf']
    data_dir = 'c:/Users/Vinicius/Desktop/Yes or No/OldMan/data'
    iphone_link_lib = ['s3eIOSGameCenter', 's3eWebView', 's3eFacebook', 'FlurryAnalytics', 's3eFlurry']
    osx_ext_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/osx/libs3eWebView.dylib', 'c:/marmalade/7.4.1/extensions/pvrtextool/lib/osx/libPVRTexTool.dylib', 'c:/marmalade/7.4.1/extensions/s3eflurry/lib/osx/libs3eFlurry.dylib']
    wp81_extra_pri = []
    ws8_ext_capabilities = []
    android_external_res = ['c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook-android-sdk/facebook/res']
    win32_ext_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/win32/s3eWebView.dll', 'c:/marmalade/7.4.1/extensions/pvrtextool/lib/win32/PVRTexTool.dll', 'c:/marmalade/7.4.1/extensions/s3eflurry/lib/win32/s3eFlurry.dll']
    wp8_ext_capabilities = []
    ws81_ext_managed_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/ws81/s3eWebViewManaged.winmd', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/ws81/s3eFacebookManaged.winmd', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_ws81_lib/Facebook.Client.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_ws8_lib/Facebook.dll']
    iphone_link_libdir = ['c:/marmalade/7.4.1/extensions/s3eiosgamecenter/lib/iphone', 'c:/marmalade/7.4.1/extensions/s3ewebview/lib/iphone', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/iphone', 'c:/marmalade/7.4.1/extensions/s3eflurry/lib/iphone']
    wp81_ext_capabilities = []
    android_extra_application_manifest = ['c:/marmalade/7.4.1/extensions/s3efacebook/source/android/extra_app_manifest.xml']
    ws8_ext_native_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/ws8/s3eWebViewExtension.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/ws8/s3eFacebookExtension.dll']
    android_external_assets = []
    blackberry_extra_descriptor = []
    ws8_extra_res = []
    android_extra_manifest = []
    wp81_ext_sdk_ref = []
    iphone_link_libdirs = []
    wp81_ext_device_capabilities = []
    linux_ext_lib = []
    ws8_ext_managed_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/ws8/s3eWebViewManaged.winmd', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/ws8/s3eFacebookManaged.winmd', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_ws8_lib/Facebook.Client.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_ws8_lib/Facebook.dll']
    ws8_ext_sdk_manifest_part = []
    ws8_ext_device_capabilities = []
    ws81_extra_pri = []
    iphone_appid = 'com.yesorno.treacherouscolors'
    android_external_jars = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/android/s3eWebView.jar', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/android/s3eFacebook.jar', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook-android-sdk/libs/android-support-v4.jar', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook-android-sdk/libs/bolts.jar', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/android/annotations-4.1.1.4.jar', 'c:/marmalade/7.4.1/extensions/s3eflurry/lib/android/s3eFlurry.jar', 'c:/marmalade/7.4.1/extensions/s3eflurry/lib/android/FlurryAgent.jar']
    win8_winrt_extra_res = ['c:/marmalade/7.4.1/extensions/s3ewebview/source/ws8/WebViewModal.xaml=>']
    wp81_ext_sdk_manifest_part = []
    android_supports_gl_texture = []
    wp81_extra_res = ['c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_wp81_lib/Facebook.Client']
    wp81_ext_managed_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/wp81/s3eWebViewManaged.winmd', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/wp81/s3eFacebookManaged.winmd', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_wp81_lib/Facebook.Client.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_wp81_lib/Facebook.dll']
    ws81_ext_sdk_manifest_part = []
    ws81_ext_device_capabilities = []
    ws8_ext_sdk_ref = []
    iphone_extra_string = []
    tizen_so = []
    wp8_ext_native_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/wp8/s3eWebViewExtension.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/wp8/s3eFacebookExtension.dll', 'c:/marmalade/7.4.1/extensions/s3eflurry/lib/wp8/s3eFlurryExtension.dll']
    iphone_bundle_url_name = 'com.yesorno.treacherouscolors'
    win8_phone_extra_res = []
    win8_store_extra_res = ['c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_ws8_lib/Facebook.Client']
    iphone_link_opts = ['-F$MARMALADE_ROOT/extensions/s3eFacebook/third-party/facebook-ios-sdk -framework FacebookSDK -weak_framework AdSupport -weak_framework Accounts -weak_framework Social -lsqlite3', '-framework SystemConfiguration -framework Security']
    ws81_ext_sdk_ref = []
    wp8_extra_res = ['c:/marmalade/7.4.1/extensions/s3ewebview/source/wp8/WebBrowserModal.xaml=>']
    ws81_ext_native_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/ws81/s3eWebViewExtension.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/ws81/s3eFacebookExtension.dll']
    ws8_extra_pri = []
    wp8_ext_managed_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/wp8/s3eWebViewManaged.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/wp8/s3eFacebookManaged.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_wp8_lib/Facebook.Client.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/third-party/facebook_wp8_lib/Facebook.dll', 'c:/marmalade/7.4.1/extensions/s3eflurry/lib/wp8/FlurryWP8SDK.dll', 'c:/marmalade/7.4.1/extensions/s3eflurry/lib/wp8/s3eFlurryManaged.dll']
    android_so = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/android/libs3eWebView.so', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/android/libs3eFacebook.so', 'c:/marmalade/7.4.1/extensions/s3eflurry/lib/android/libs3eFlurry.so']
    wp8_ext_sdk_ref = []
    iphone_bundle_url_schemes = 'fb<955358454521782>'
    osx_extra_res = []
    ws81_extra_res = []
    wp81_ext_native_dll = ['c:/marmalade/7.4.1/extensions/s3ewebview/lib/wp81/s3eWebViewExtension.dll', 'c:/marmalade/7.4.1/extensions/s3efacebook/lib/wp81/s3eFacebookExtension.dll']
    ws81_ext_capabilities = []
    iphone_link_libs = []
    target = {
         'gcc_x86' : {
                   'debug'   : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Debug_OldMan_VC12X_gcc_x86/OldMan.so',
                   'release' : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Release_OldMan_VC12X_gcc_x86/OldMan.so',
                 },
         'gcc_x86_tizen' : {
                   'debug'   : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Debug_OldMan_VC12X_gcc_x86_tizen/OldMan.s86',
                   'release' : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Release_OldMan_VC12X_gcc_x86_tizen/OldMan.s86',
                 },
         'firefoxos' : {
                   'debug'   : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Debug_OldMan_VC12X_firefoxos/OldMan.js',
                   'release' : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Release_OldMan_VC12X_firefoxos/OldMan.js',
                 },
         'mips_gcc' : {
                   'debug'   : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Debug_OldMan_VC12X_gcc_mips/OldMan.so',
                   'release' : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Release_OldMan_VC12X_gcc_mips/OldMan.so',
                 },
         'arm_gcc' : {
                   'debug'   : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Debug_OldMan_VC12X_gcc_arm/OldMan.s3e',
                   'release' : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Release_OldMan_VC12X_gcc_arm/OldMan.s3e',
                 },
         'mips' : {
                   'debug'   : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Debug_OldMan_VC12X_gcc_mips/OldMan.so',
                   'release' : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Release_OldMan_VC12X_gcc_mips/OldMan.so',
                 },
         'gcc_x86_android' : {
                   'debug'   : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Debug_OldMan_VC12X_gcc_x86_android/OldMan.so',
                   'release' : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Release_OldMan_VC12X_gcc_x86_android/OldMan.so',
                 },
         'arm' : {
                   'debug'   : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Debug_OldMan_VC12X_arm/OldMan.s3e',
                   'release' : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Release_OldMan_VC12X_arm/OldMan.s3e',
                 },
         'x86' : {
                   'debug'   : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Debug_OldMan_VC12X_x86/OldMan.s86',
                   'release' : r'c:/Users/Vinicius/Desktop/Yes or No/OldMan/build_oldman_vc12x/Release_OldMan_VC12X_x86/OldMan.s86',
                 },
        }
    arm_arch = ''
    assets_original = assets
    assets = assets['Default']

default = DefaultConfig()