namespace arkostracker 
{

//#include "../../catch.hpp"



//#include "../../../source/ui/containerArranger/ViewArranger.h"
//#include "../../../source/ui/containerArranger/PanelSizes.h"

/** Tests the ViewArranger. */
// TODO ViewArranger tests ignored for now.


/** An implementation of an ArrangerView, to allow settings the sizes quickly. */
/*
class ArrangerViewImpl : public ArrangerView
{
public:
    explicit ArrangerViewImpl(int pWidth, int pHeight, int pDesiredSize, int pMinimumSize = 30, int pLockedSize = 0, bool pHiddenHeader = false) :
            desiredSize(pDesiredSize),
            minimumSize(pMinimumSize),
            lockedSize(pLockedSize),
            hiddenHeader(pHiddenHeader)
    {
        setSize(pWidth, pHeight);
    }

    Dimension getArrangerViewWidth() const noexcept override
    {
        return Dimension(lockedSize, minimumSize, lockedSize + 100);
    }

    Dimension getArrangerViewHeight() const noexcept override
    {
        return Dimension(lockedSize, minimumSize, lockedSize + 100);
    }

    bool isHiddenHeader() const override
    {
        return hiddenHeader;
    }

private:
    const int desiredSize;
    const int minimumSize;
    const int lockedSize;
    const bool hiddenHeader;
};
*/





// ===================================================================




/*

TEST_CASE("oneVerticalContainerAloneToStretch", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl view1(500, 600, 0);
    auto views = std::vector<ArrangerView*> { &view1 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const auto& outputView1 = views.at(0);
    REQUIRE(outputView1->getSize(dimension) == parentHeight);
    REQUIRE(outputView1->getHeight() == parentHeight);
    REQUIRE(outputView1->getWidth() == parentWidth);
}

TEST_CASE("oneVerticalContainerToStretchSize0", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(500, 0, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    // Handle 1.
    size_t index = 0;
    {
        const auto& outputView1 = views.at(index);
        REQUIRE(outputView1->getSize(dimension) == handleSize);
        REQUIRE(outputView1->getHeight() == handleSize);
        REQUIRE(outputView1->getWidth() == parentWidth);
    }

    // Main view.
    {
        const auto& outputView2 = views.at(++index);
        const int REQUIREedHeightView2 = parentHeight - 2 * handleSize;
        REQUIRE(outputView2->getSize(dimension) == REQUIREedHeightView2);
        REQUIRE(outputView2->getHeight() == REQUIREedHeightView2);
        REQUIRE(outputView2->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& outputView3 = views.at(++index);
        REQUIRE(outputView3->getSize(dimension) == handleSize);
        REQUIRE(outputView3->getHeight() == handleSize);
        REQUIRE(outputView3->getWidth() == parentWidth);
    }
}

TEST_CASE("oneVerticalContainerToStretch", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(500, 600, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    // Handle 1.
    size_t index = 0;
    {
        const auto& outputView1 = views.at(index);
        REQUIRE(outputView1->getSize(dimension) == handleSize);
        REQUIRE(outputView1->getHeight() == handleSize);
        REQUIRE(outputView1->getWidth() == parentWidth);
    }

    // Main view.
    {
        const auto& outputView2 = views.at(++index);
        const int REQUIREedHeightView2 = parentHeight - 2 * handleSize;
        REQUIRE(outputView2->getSize(dimension) == REQUIREedHeightView2);
        REQUIRE(outputView2->getHeight() == REQUIREedHeightView2);
        REQUIRE(outputView2->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& outputView3 = views.at(++index);
        REQUIRE(outputView3->getSize(dimension) == handleSize);
        REQUIRE(outputView3->getHeight() == handleSize);
        REQUIRE(outputView3->getWidth() == parentWidth);
    }
}


TEST_CASE("oneHorizontalContainerToStretch", "[ViewArranger]")
{
    const auto dimension = Dimension::width;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 800;
    const int parentHeight = 1000;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl viewHandle1(handleSize, 200, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(handleSize, 400, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(600, 500, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2 };

    // When.
    // ====================
    ViewArranger viewArranger(true, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    // Handle 1.
    size_t index = 0;
    {
        const auto& outputView1 = views.at(index);
        REQUIRE(outputView1->getSize(dimension) == handleSize);
        REQUIRE(outputView1->getWidth() == handleSize);
        REQUIRE(outputView1->getHeight() == parentHeight);
    }

    // Main view.
    {
        const auto& outputView2 = views.at(++index);
        const int REQUIREedWidthView2 = parentWidth - 2 * handleSize;
        REQUIRE(outputView2->getSize(dimension) == REQUIREedWidthView2);
        REQUIRE(outputView2->getWidth() == REQUIREedWidthView2);
        REQUIRE(outputView2->getHeight() == parentHeight);
    }

    // Handle 2.
    {
        const auto& outputView3 = views.at(++index);
        REQUIRE(outputView3->getSize(dimension) == handleSize);
        REQUIRE(outputView3->getWidth() == handleSize);
        REQUIRE(outputView3->getHeight() == parentHeight);
    }
}

TEST_CASE("twoVerticalContainersToStretch", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Three handles, and two views in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(2000, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(200, 200, 0);
    ArrangerViewImpl view2(1200, 300, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int spaceForViews = (parentHeight - 3 * handleSize - 200 - 300) / 2;

    // Handle 1.
    size_t index = 0;
    {
        const auto& handleView = views.at(index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 1.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 200 + spaceForViews + 1;         // +1 because there is one pixel left, so it is added in a second pass.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 2.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 300 + spaceForViews;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }
}

TEST_CASE("oneVerticalContainerToStretchWithTopOffset", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Three handles, and two views in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(2000, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(200, 200, 0);
    ArrangerViewImpl view2(1200, 300, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    const int topOffset = 50;
    ViewArranger viewArranger(false, topOffset);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int spaceForViews = (parentHeight - topOffset - 3 * handleSize - 200 - 300) / 2;

    // Handle 1.
    size_t index = 0;
    {
        const auto& handleView = views.at(index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 1.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 200 + spaceForViews + 1;         // +1 because there is one pixel left, so it is added in a second pass.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 2.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 300 + spaceForViews;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }
}

TEST_CASE("twoVerticalContainersToStretchWithOneWithDesireAndSize0AtFirst", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Three handles, and two views in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    // The view 2 will only increase up to its desired size.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(2000, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(200, 200, 0);
    ArrangerViewImpl view2(1200, 0, 100);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int headerSize = PanelSizes::headerHeight;

    // Handle 1.
    size_t index = 0;
    {
        const auto& handleView = views.at(index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 1.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = parentHeight - 3 * handleSize - 100 - headerSize;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 2.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 100 + headerSize;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }
}

TEST_CASE("threeVerticalContainersToStretch", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(2000, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle4(100, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(200, 200, 0);
    ArrangerViewImpl view2(1200, 300, 0);
    ArrangerViewImpl view3(50, 100, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3, &view3, &viewHandle4 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int spaceForViews = (parentHeight - 4 * handleSize - 200 - 300 - 100) / 3;

    // Handle 1.
    size_t index = 0;
    {
        const auto& handleView = views.at(index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 1.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 200 + spaceForViews + 1;         // +1 added in second pass because of rounding.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 2.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 300 + spaceForViews + 1;         // +1 added in second pass because of rounding.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 3.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 100 + spaceForViews;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 4.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }
}

TEST_CASE("oneVerticalContainerToStretchButDesiredSize", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    // However, the desired size is reached. Since we have no choice, this view is stretched anyway.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(500, 200, 200);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    // Handle 1.
    size_t index = 0;
    {
        const auto& outputView1 = views.at(index);
        REQUIRE(outputView1->getSize(dimension) == handleSize);
        REQUIRE(outputView1->getHeight() == handleSize);
        REQUIRE(outputView1->getWidth() == parentWidth);
    }

    // Main view.
    {
        const auto& outputView2 = views.at(++index);
        const int REQUIREedHeightView2 = parentHeight - 2 * handleSize;
        REQUIRE(outputView2->getSize(dimension) == REQUIREedHeightView2);
        REQUIRE(outputView2->getHeight() == REQUIREedHeightView2);
        REQUIRE(outputView2->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& outputView3 = views.at(++index);
        REQUIRE(outputView3->getSize(dimension) == handleSize);
        REQUIRE(outputView3->getHeight() == handleSize);
        REQUIRE(outputView3->getWidth() == parentWidth);
    }
}

TEST_CASE("twoVerticalContainersToStretchButDesiredSize", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    // However, the desired size is reached. Since we have no choice, this view is stretched anyway.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(100, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(500, 200, 200, 30, 0, true);
    ArrangerViewImpl view2(500, 200, 200, 30, 0, true);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int REQUIREedHeightViews = (parentHeight - 3 * handleSize) / 2;

    // Handle 1.
    size_t index = 0;
    {
        const auto& outputView = views.at(index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // View 1.
    {
        const auto& outputView = views.at(++index);
        const auto REQUIREedHeight = REQUIREedHeightViews + 1;        // +1 because of the rounding.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeight);
        REQUIRE(outputView->getHeight() == REQUIREedHeight);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& outputView = views.at(++index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // View 2.
    {
        const auto& outputView = views.at(++index);
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightViews);
        REQUIRE(outputView->getHeight() == REQUIREedHeightViews);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& outputView = views.at(++index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }
}

TEST_CASE("twoVerticalContainersToStretchButFirstViewHasJustTheDesiredSizeWithHeader", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, only the view2 should be resized because the first has reached its desired size.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(2000, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(200, 200, 200 - PanelSizes::headerHeight);       // The header is present.
    ArrangerViewImpl view2(1200, 300, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int spaceForViews = (parentHeight - 3 * handleSize - 200 - 300);

    // Handle 1.
    size_t index = 0;
    {
        const auto& handleView = views.at(index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 1.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 200;             // Not resized.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 2.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 300 + spaceForViews;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }
}

TEST_CASE("twoVerticalContainersToStretchButFirstViewHasJustTheDesiredSizeWithoutHeader", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, only the view2 should be resized because the first has reached its desired size.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(2000, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(200, 200, 200, 30, 0, true);       // No header is present.
    ArrangerViewImpl view2(1200, 300, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int spaceForViews = (parentHeight - 3 * handleSize - 200 - 300);

    // Handle 1.
    size_t index = 0;
    {
        const auto& handleView = views.at(index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 1.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 200;             // Not resized.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 2.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 300 + spaceForViews;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }
}

TEST_CASE("twoVerticalContainersToStretchButFirstViewHasBelowTheDesiredSizeNoHeader", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, only the view2 should be resized because the first has reached its desired size.
    // But view1 is going to be stretch up to its desired size.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(2000, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(200, 100, 200, 30, 0, true);       // Current height is smaller than desired. No header is present.
    ArrangerViewImpl view2(1200, 300, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int spaceForViews = (parentHeight - 3 * handleSize - 200 - 300);

    // Handle 1.
    size_t index = 0;
    {
        const auto& handleView = views.at(index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 1.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 200;             // Resized up to this size.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 2.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 300 + spaceForViews;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }
}

TEST_CASE("threeVerticalContainersToStretchButFirstAndThirdViewHaveBelowTheDesiredSizeNoHeader", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 900;       // I cheated a bit: increased the height a bit so that the view1 can reach its desired size.
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(2000, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle4(100, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(200, 100, 200, 30, 0, true);
    ArrangerViewImpl view2(1200, 300, 0, 30, 0, true);
    ArrangerViewImpl view3(50, 90, 100, 30, 0, true);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3, &view3, &viewHandle4 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int spaceForSecondView = (parentHeight - 4 * handleSize - 200 - 100);

    // Handle 1.
    size_t index = 0;
    {
        const auto& handleView = views.at(index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 1.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 200;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 2.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = spaceForSecondView;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 3.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 100;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 4.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }
}


// ------------------------------------------------

TEST_CASE("oneVerticalContainerAloneToShrink", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 800;
    const int parentHeight = 1000;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(500, 1500, 0);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    // Handle 1.
    size_t index = 0;
    {
        const auto& outputView1 = views.at(index);
        REQUIRE(outputView1->getSize(dimension) == handleSize);
        REQUIRE(outputView1->getHeight() == handleSize);
        REQUIRE(outputView1->getWidth() == parentWidth);
    }

    // Main view.
    {
        const auto& outputView2 = views.at(++index);
        const int REQUIREedHeightView2 = parentHeight - 2 * handleSize;
        REQUIRE(outputView2->getSize(dimension) == REQUIREedHeightView2);
        REQUIRE(outputView2->getHeight() == REQUIREedHeightView2);
        REQUIRE(outputView2->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& outputView3 = views.at(++index);
        REQUIRE(outputView3->getSize(dimension) == handleSize);
        REQUIRE(outputView3->getHeight() == handleSize);
        REQUIRE(outputView3->getWidth() == parentWidth);
    }
}

TEST_CASE("threeVerticalContainersToShrink", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Two handles, and a view in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 800;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The height is not full in the parent, but since we have room it should stretch.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(2000, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle4(100, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(200, 500, 0, 30, 0, true);
    ArrangerViewImpl view2(1200, 600, 0, 30, 0, true);
    ArrangerViewImpl view3(50, 700, 0, 30, 0, true);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3, &view3, &viewHandle4 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    const int usedSpace = 4 * handleSize + 500 + 600 + 700;
    const int spaceToSave = std::abs(parentHeight - usedSpace) / 3;

    // Handle 1.
    size_t index = 0;
    {
        const auto& handleView = views.at(index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 1.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 500 - spaceToSave - 1;       // -1 due to rounding.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 2.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 600 - spaceToSave;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }

    // Main view 3.
    {
        const auto& outputView = views.at(++index);
        const int REQUIREedHeightView = 700 - spaceToSave;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeightView);
        REQUIRE(outputView->getHeight() == REQUIREedHeightView);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 4.
    {
        const auto& handleView = views.at(++index);
        REQUIRE(handleView->getSize(dimension) == handleSize);
        REQUIRE(handleView->getHeight() == handleSize);
        REQUIRE(handleView->getWidth() == parentWidth);
    }
}

TEST_CASE("twoVerticalContainersToShrinkButDesiredSize", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Three handles, and two views in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 200;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // The desired size is reached. Since we have no choice, this view is stretched anyway.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(100, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(500, 400, 300, 30, 0, true);
    ArrangerViewImpl view2(500, 500, 300, 30, 0, true);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    // The height does not take the desired in account, they are overridden because there is not enough space.
    const int REQUIREHeights = (parentHeight - 3 * handleSize) / 2;

    // Handle 1.
    size_t index = 0;
    {
        const auto& outputView = views.at(index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // View 1.
    {
        const auto& outputView = views.at(++index);
        const auto REQUIREedHeight = REQUIREHeights;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeight);
        REQUIRE(outputView->getHeight() == REQUIREedHeight);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& outputView = views.at(++index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // View 2.
    {
        const auto& outputView = views.at(++index);
        const auto REQUIREedHeight = REQUIREHeights + 1;      // Due to rounding.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeight);
        REQUIRE(outputView->getHeight() == REQUIREedHeight);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& outputView = views.at(++index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }
}

TEST_CASE("twoVerticalContainersToShrinkButOneReachedMinimumSize", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Three handles, and two views in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 400;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // Lacks of space, but view 1 will reach its minimum size, so view 2 will be more shrunk.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(100, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(500, 400, 0, 300, 0, true);
    ArrangerViewImpl view2(500, 400, 0, 30, 0, true);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    // Handle 1.
    size_t index = 0;
    {
        const auto& outputView = views.at(index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // View 1.
    {
        const auto& outputView = views.at(++index);
        const auto REQUIREedHeight = 300;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeight);
        REQUIRE(outputView->getHeight() == REQUIREedHeight);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& outputView = views.at(++index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // View 2.
    {
        const auto& outputView = views.at(++index);
        const auto REQUIREedHeight = 100 - 3 * handleSize;           // Only this remains.
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeight);
        REQUIRE(outputView->getHeight() == REQUIREedHeight);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& outputView = views.at(++index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }
}

TEST_CASE("twoVerticalContainersToShrinkButBothReachedMinimumSize", "[ViewArranger]")
{
    const auto dimension = Dimension::height;

    // Given.
    // ====================
    // Three handles, and two views in the middle.
    juce::Component parentComponent;
    const int parentWidth = 1000;
    const int parentHeight = 50;
    const int handleSize = 3;
    parentComponent.setSize(parentWidth, parentHeight);

    // Lacks of space, both views will get stuck to their minimum, even if it means going beyond the screen limit.
    ArrangerViewImpl viewHandle1(200, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle2(400, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl viewHandle3(100, handleSize, handleSize, handleSize, handleSize);
    ArrangerViewImpl view1(500, 400, 0, 30, 0, true);
    ArrangerViewImpl view2(500, 400, 0, 40, 0, true);
    auto views = std::vector<ArrangerView*> { &viewHandle1, &view1, &viewHandle2, &view2, &viewHandle3 };

    // When.
    // ====================
    ViewArranger viewArranger(false, 0);
    viewArranger.onResized(parentComponent, views);

    // Then.
    // ====================
    // Handle 1.
    size_t index = 0;
    {
        const auto& outputView = views.at(index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // View 1.
    {
        const auto& outputView = views.at(++index);
        const auto REQUIREedHeight = 30;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeight);
        REQUIRE(outputView->getHeight() == REQUIREedHeight);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 2.
    {
        const auto& outputView = views.at(++index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // View 2.
    {
        const auto& outputView = views.at(++index);
        const auto REQUIREedHeight = 40;
        REQUIRE(outputView->getSize(dimension) == REQUIREedHeight);
        REQUIRE(outputView->getHeight() == REQUIREedHeight);
        REQUIRE(outputView->getWidth() == parentWidth);
    }

    // Handle 3.
    {
        const auto& outputView = views.at(++index);
        REQUIRE(outputView->getSize(dimension) == handleSize);
        REQUIRE(outputView->getHeight() == handleSize);
        REQUIRE(outputView->getWidth() == parentWidth);
    }
}*/


}   // namespace arkostracker

