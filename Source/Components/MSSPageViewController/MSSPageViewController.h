//
//  MSSTabbedPageViewController.h
//  TabbedPageViewController
//
//  Created by Merrick Sapsford on 24/12/2015.
//  Copyright © 2015 Merrick Sapsford. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UIViewController+MSSUtilities.h"
#import "UIView+MSSAutoLayout.h"

extern NSInteger const MSSPageViewControllerPageNumberInvalid;

typedef NS_ENUM(NSInteger, MSSPageViewControllerScrollDirection) {
    MSSPageViewControllerScrollDirectionUnknown = -1,
    MSSPageViewControllerScrollDirectionBackward = 0,
    MSSPageViewControllerScrollDirectionForward = 1
};

typedef NS_ENUM(NSInteger, MSSPageViewControllerInfinitePagingBehavior) {
    /**
     The infinite page behavior will be standard.
     
     I.e. Going from last index to index 0 will have a forward transition,
     index 0 to last index will have a reverse transition.
     */
    MSSPageViewControllerInfinitePagingBehaviorStandard,
    /**
     The infinite page behavior will be reversed.
     
     I.e. Going from last index to index 0 will have a reverse transition,
     index 0 to last index will have a forward transition.
     */
    MSSPageViewControllerInfinitePagingBehaviorReversed
};

typedef void(^MSSPageViewControllerPageMoveCompletion)(UIViewController *_Nullable newViewController, BOOL animated, BOOL transitionFinished);

@class MSSPageViewController;

@protocol MSSPageViewControllerDelegate <NSObject>
@optional

/**
 The page view controller has scrolled to a new page offset.
 
 @param pageViewController
        The page view controller.
 @param pageOffset
        The updated page offset.
 */
- (void)pageViewController:(nonnull MSSPageViewController *)pageViewController
     didScrollToPageOffset:(CGFloat)pageOffset
                 direction:(MSSPageViewControllerScrollDirection)scrollDirection;
/**
 The page view controller has started a scroll to a new page.
 
 @param pageViewController
 The page view controller.
 @param newPage
 The new visible page.
 @param currentPage
 The new currently visible page.
 */
- (void)pageViewController:(nonnull MSSPageViewController *)pageViewController
          willScrollToPage:(NSInteger)newPage
               currentPage:(NSInteger)currentPage;
/**
 The page view controller has completed scroll to a page.
 
 @param pageViewController
 The page view controller.
 @param page
 The new currently visible page.
 @param oldPage
 The old page.
 */
- (void)pageViewController:(nonnull MSSPageViewController *)pageViewController
           didScrollToPage:(NSInteger)page
                   oldPage:(NSInteger)oldPage;

/**
 The page view controller has successfully prepared child view controllers ready for display.
 
 @param pageViewController
 The page view controller.
 @param viewControllers
 The view controllers inside the page view controller.
 */
- (void)pageViewController:(nonnull MSSPageViewController *)pageViewController
 didPrepareViewControllers:(nonnull NSArray *)viewControllers;
/**
 The page view controller will display the initial view controller.
 
 @param pageViewController
 The page view controller.
 @param viewController
 The initial view controller.
 */
- (void)pageViewController:(nonnull MSSPageViewController *)pageViewController
willDisplayInitialViewController:(nonnull UIViewController *)viewController;

@end

@protocol MSSPageViewControllerDataSource <NSObject>

/**
 The view controllers to display in the page view controller.
 
 @param pageViewController
 The page view controller.
 @return The array of view controllers.
 */
- (nullable NSArray<UIViewController *> *)viewControllersForPageViewController:(nonnull MSSPageViewController *)pageViewController;

@optional
- (nullable UIViewController *)beforeViewController:(NSInteger)currentIndex nextIndex:(NSInteger)nextIndex;

/**
 The default page index for the page view controller to initially display.
 
 @param pageViewController
 The page view controller.
 @return The default page index.
 */
- (NSInteger)defaultPageIndexForPageViewController:(nonnull MSSPageViewController *)pageViewController;

@end

@interface MSSPageViewController : UIViewController <MSSPageViewControllerDelegate, MSSPageViewControllerDataSource, UIScrollViewDelegate>

/**
 The object that acts as a data source for the page view controller.
 */
@property (nonatomic, weak, nullable) IBOutlet id<MSSPageViewControllerDataSource> dataSource;
/**
 The object that acts as a delegate for the page view controller.
 */
@property (nonatomic, weak, nullable) IBOutlet id<MSSPageViewControllerDelegate> delegate;

/**
 The number of pages in the page view controller.
 */
@property (nonatomic, assign ,readonly) NSInteger numberOfPages;
/**
 The current active page index of the page view controller.
 */
@property (nonatomic, assign, readonly) NSInteger currentPage;
/**
 The view controllers within the page view controller.
 */
@property (nonatomic, strong, readonly, nullable) NSArray<UIViewController *> *viewControllers;

/**
 Whether page view controller will display the page indicator view.
 */
@property (nonatomic, assign) BOOL showPageIndicator;

/**
 Whether page view controller will provide delegate updates on scroll events.
 */
@property (nonatomic, assign) BOOL allowScrollViewUpdates;
/**
 Whether the user is currently dragging the page view controller.
 */
@property (nonatomic, assign, readonly) BOOL isDragging;
/**
 Whether scroll view interaction is enabled on the page view controller.
 */
@property (nonatomic, assign, getter=isScrollEnabled) BOOL scrollEnabled;
/**
 Whether user interaction is allowed on the page view controller.
 */
@property (nonatomic, assign) BOOL userInteractionEnabled;
/**
 Whether page view controller will provide scroll updates when out of bounds.
 */
@property (nonatomic, assign, getter=willProvideOutOfBoundsUpdates) BOOL provideOutOfBoundsUpdates;
/**
 Whether the page view controller is currently animating a page update.
 */
@property (nonatomic, assign, readonly, getter=isAnimatingPageUpdate) BOOL animatingPageUpdate;
/**
 Allows the page view controller to scroll indefinitely when it reaches end of page range.
 */
@property (nonatomic, assign, getter=hasInfiniteScrollEnabled) BOOL infiniteScrollEnabled;
/**
 The paging behavior to use when infinite scroll is enabled. This adjusts page transition animations
 when using moveToPageAtIndex functions. MSSPageViewControllerInfinitePagingBehaviorStandard by default.
 */
@property (nonatomic, assign) MSSPageViewControllerInfinitePagingBehavior infiniteScrollPagingBehaviour;

@property (nonatomic, assign) BOOL bounce;

/**
 Move page view controller to a page at specific index.
 
 @param index
 The index of the page to display.
 */
- (void)moveToPageAtIndex:(NSInteger)index;

/**
 Move page view controller to a page at specific index.
 
 @param index
 The index of the page to display.
 @param completion
 Completion of the page move.
 */
- (void)moveToPageAtIndex:(NSInteger)index
               completion:(nullable MSSPageViewControllerPageMoveCompletion)completion;

/**
 Move page view controller to a page at specific index.
 
 @param index
 The index of the page to display.
 @param animated
 Whether to animate the page transition.
 @param completion
 Completion of the page move.
 */
- (void)moveToPageAtIndex:(NSInteger)index
                 animated:(BOOL)animated
               completion:(nullable MSSPageViewControllerPageMoveCompletion)completion;


/** UIScrollViewDelegate */
- (void)scrollViewWillBeginDragging:(nonnull UIScrollView *)scrollView NS_REQUIRES_SUPER;
- (void)scrollViewDidScroll:(nonnull UIScrollView *)scrollView NS_REQUIRES_SUPER;

@end

@interface UIViewController (MSSPageViewController)

/**
 The page view controller of the parent
 */
@property (nonatomic, weak, readonly, nullable) MSSPageViewController *pageViewController;
/**
 The index of the current view controller
 */
@property (nonatomic, assign, readonly) NSInteger pageIndex;

@end
