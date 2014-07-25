/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

#import "RootViewController.h"
#import "cocos2d.h"
#import "CCEAGLView.h"
#import "GADBannerView.h"
#import <iAd/iAd.h>

@interface RootViewController()<GADBannerViewDelegate,ADBannerViewDelegate>
{
}
@property (atomic,assign) BOOL adViewHidden;
@property (atomic,assign) BOOL iadViewHidden;
@property (nonatomic, strong) GADBannerView * adView;
@property (nonatomic, strong) ADBannerView* iAdView;
@end

RootViewController* rootvc=NULL;

void showAd()
{
    rootvc.adView.hidden=rootvc.adViewHidden;
    rootvc.iAdView.hidden=rootvc.iadViewHidden;
}

void hideAd()
{
    rootvc.adView.hidden=true;
    rootvc.iAdView.hidden=true;
}

@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

- (void)adViewDidReceiveAd:(GADBannerView *)view
{
    _adView.center = CGPointMake(self.view.frame.size.width/2, self.view.frame.size.height-view.frame.size.height/2);
}

/// Called when an ad request failed. Normally this is because no network connection was available
/// or no ads were available (i.e. no fill). If the error was received as a part of the server-side
/// auto refreshing, you can examine the hasAutoRefreshed property of the view.
- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error
{
    
}

- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    
    self.iAdView.hidden=true;
    self.iadViewHidden=true;
    self.adViewHidden=false;
    [self.view addSubview:_adView];
    
    [_adView setHidden:true];
    _adView.center = CGPointMake(self.view.frame.size.width/2, self.view.frame.size.height-_adView.frame.size.height/2);
    
    // Инициирование общего запроса на загрузку с объявлением.
    [_adView loadRequest:[GADRequest request]];
}
- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    [self.view bringSubviewToFront:self.iAdView];
}
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    self.adViewHidden=true;
    self.iadViewHidden=false;
    
    rootvc=self;
    if (self.view.frame.size.width>=768)
        self.iAdView=[[ADBannerView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height-66,
                                                                    self.view.frame.size.width,
                                                                      66)];
    else
        self.iAdView=[[ADBannerView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height-50,
                                                                    self.view.frame.size.width,
                                                                          50)];
    
    self.iAdView.delegate=self;
    
    [self.view addSubview:self.iAdView];
    
                        
    GADAdSize bannerSize=kGADAdSizeBanner;
    if (self.view.frame.size.width>=768)
        bannerSize=kGADAdSizeLeaderboard;
    
    _adView = [[GADBannerView alloc] initWithAdSize:bannerSize];
    
    // Указание идентификатора рекламного блока.
    _adView.adUnitID = @"ca-app-pub-8430244079488991/2421601847";
    
    // Укажите, какой UIViewController необходимо восстановить
    // после перехода пользователя по объявлению и добавить в иерархию представлений.
    _adView.rootViewController = self;
    _adView.delegate=self;
    

    
}


// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


@end
