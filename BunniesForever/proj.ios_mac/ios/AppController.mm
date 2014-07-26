/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "CCEAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"

#import "Flurry.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)devToken {
    
    NSString *appName = [[[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleIdentifier"]
                         stringByReplacingOccurrencesOfString:@"." withString:@"_"];
    
    NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"];
    
    // Check what Notifications the user has turned on.  We registered for all three, but they may have manually disabled some or all of them.
    
    NSUInteger rntypes = [[UIApplication sharedApplication] enabledRemoteNotificationTypes];
    
    
    
    // Set the defaults to disabled unless we find otherwise...
    
    NSString *pushBadge = @"disabled";
    
    NSString *pushAlert = @"disabled";
    
    NSString *pushSound = @"disabled";
    
    
    
    // Check what Registered Types are turned on. This is a bit tricky since if two are enabled, and one is off, it will return a number 2... not telling you which
    
    // one is actually disabled. So we are literally checking to see if rnTypes matches what is turned on, instead of by number. The "tricky" part is that the
    
    // single notification types will only match if they are the ONLY one enabled.  Likewise, when we are checking for a pair of notifications, it will only be
    
    // true if those two notifications are on.  This is why the code is written this way
    
    if(rntypes & UIRemoteNotificationTypeBadge ){
    
        pushBadge = @"enabled";
        
    }
    
    if(rntypes & UIRemoteNotificationTypeAlert){
        
        pushAlert = @"enabled";
        
    }
    
    if(rntypes & UIRemoteNotificationTypeSound){
        
        pushSound = @"enabled";
        
    }
    
    
    
    // Get the users Device Model, Display Name, Unique ID, Token & Version Number
    
    UIDevice *dev = [UIDevice currentDevice];
    
    NSString *deviceName = dev.name;
    
    NSString *deviceModel = dev.model;
    
    NSString *deviceSystemVersion = dev.systemVersion;
    
    
    
    // Prepare the Device Token for Registration (remove spaces and < >)
    
    NSString *deviceToken = [[[[devToken description]
                               
                               stringByReplacingOccurrencesOfString:@"<" withString:@""]
                              
                              stringByReplacingOccurrencesOfString:@">" withString:@""]
                             
                             stringByReplacingOccurrencesOfString: @" " withString: @""];
    
    
    
    // Build URL String for Registration
    
    // !!! CHANGE "www.mywebsite.com" TO YOUR WEBSITE. Leave out the http://
    
    // !!! SAMPLE: "secure.awesomeapp.com"
    
    NSString *host = @"kiyanov.com/apns";
    
    
    
    // !!! CHANGE "/apns.php?" TO THE PATH TO WHERE apns.php IS INSTALLED
    
    // !!! ( MUST START WITH / AND END WITH ? ).
    
    // !!! SAMPLE: "/path/to/apns.php?"
    
    NSString *urlString = [@"/apns.php?" stringByAppendingString:@"task=register"];
    
    
    
    urlString = [urlString stringByAppendingString:@"&appname="];
    urlString = [urlString stringByAppendingString:appName];
    
    urlString = [urlString stringByAppendingString:@"&appid="];
    urlString = [urlString stringByAppendingString:appName];
    
    urlString = [urlString stringByAppendingString:@"&appversion="];
    urlString = [urlString stringByAppendingString:appVersion];
    
    urlString = [urlString stringByAppendingString:@"&devicetoken="];
    urlString = [urlString stringByAppendingString:deviceToken];
    
    urlString = [urlString stringByAppendingString:@"&devicename="];
    urlString = [urlString stringByAppendingString:deviceName];
    
    urlString = [urlString stringByAppendingString:@"&devicemodel="];
    urlString = [urlString stringByAppendingString:deviceModel];
    
    urlString = [urlString stringByAppendingString:@"&deviceversion="];
    urlString = [urlString stringByAppendingString:deviceSystemVersion];
    
    urlString = [urlString stringByAppendingString:@"&pushbadge="];
    urlString = [urlString stringByAppendingString:pushBadge];
    
    urlString = [urlString stringByAppendingString:@"&pushalert="];
    urlString = [urlString stringByAppendingString:pushAlert];
    
    urlString = [urlString stringByAppendingString:@"&pushsound="];
    urlString = [urlString stringByAppendingString:pushSound];
    
    
    
    // Register the Device Data
    
    // !!! CHANGE "http" TO "https" IF YOU ARE USING HTTPS PROTOCOL
    
    NSURL *url = [[NSURL alloc] initWithScheme:@"http" host:host path:urlString];
    
    NSURLRequest *request = [[NSURLRequest alloc] initWithURL:url];
    
[NSURLConnection sendAsynchronousRequest:request
                                                            queue:[[NSOperationQueue alloc] init]
                                                completionHandler:^(NSURLResponse *response, NSData *data, NSError *connectionError) {
                                                        NSLog(@"Return Data: %@", data);
                                                }];
    
    NSLog(@"Register URL: %@", url);
    

    
    
    
    /*
     NSMutableString *tokenString = [NSMutableString stringWithString:
     [[deviceToken description] uppercaseString]];
     [tokenString replaceOccurrencesOfString:@"<"
     withString:@""
     options:0
     range:NSMakeRange(0, tokenString.length)];
     [tokenString replaceOccurrencesOfString:@">"
     withString:@""
     options:0
     range:NSMakeRange(0, tokenString.length)];
     [tokenString replaceOccurrencesOfString:@" "
     withString:@""
     options:0
     range:NSMakeRange(0, tokenString.length)];
     //  NSLog(@"Token: %@", tokenString);
     
     if (tokenString) {
     [[NSUserDefaults standardUserDefaults] setObject:tokenString forKey:@"token"];
     }
     
     NSString* bundleId=[[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleIdentifier"];
     NSString *urlFormat = @"http://game-era.com/apns/apns.php?token=%@&appid=%@";
     NSURL *registrationURL = [NSURL URLWithString:[NSString stringWithFormat:
     urlFormat, tokenString,bundleId]];
     
     NSMutableURLRequest *registrationRequest = [[NSMutableURLRequest alloc]
     initWithURL:registrationURL];
     [registrationRequest setHTTPMethod:@"PUT"];
     
     
     NSURLConnection *connection = [NSURLConnection connectionWithRequest:registrationRequest
     delegate:self];
     [connection start];
     [registrationRequest release];
     */
}

- (void) application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    NSLog(error.localizedDescription);
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:(UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound)];
    // Replace YOUR_API_KEY with the api key in the downloaded package
    [Flurry startSession:@"KFFY7QHHK8M4T7BN8VN7"];
    
    NSString* url = launchOptions[UIApplicationLaunchOptionsRemoteNotificationKey][@"package"];
    if (url)
    {
        [application openURL:[NSURL URLWithString:url]];
    }
    
  //  [[[UIAlertView alloc] initWithTitle:@"" message:[launchOptions[UIApplicationLaunchOptionsRemoteNotificationKey] description]
    //                           delegate:0 cancelButtonTitle:@"OK" otherButtonTitles: nil] show];
    /*
    NSAttributedString* str=[[NSAttributedString alloc] initWithString:@"Hello"];
    
    NSArray* ar=@[str];
    NSString* path=[NSTemporaryDirectory() stringByAppendingPathComponent:@"tmp.tmp"];
    BOOL success=[ar writeToFile:path atomically:YES];
    if (success)
    {
        NSLog(@"it's works");
    }
    */
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGB565
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage CCEAGLView 
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLView::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    cocos2d::Application::getInstance()->run();

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
