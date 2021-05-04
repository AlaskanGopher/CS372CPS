//
// Created by Chris Hartman on 3/5/21.
//
#include <catch2/catch.hpp>
#include "Shape.hpp"
using namespace Catch::literals; //NOLINT

TEST_CASE("Basic shapes width and height") { //NOLINT
   const auto circleRadius = 4.5521;
   auto circle = makeCircle(circleRadius);
   REQUIRE(circle->getHeight()==Approx(2*circleRadius));
   REQUIRE(circle->getWidth()==Approx(2*circleRadius));

   auto rectangle = makeRectangle(1.1,2.2);
   REQUIRE(rectangle->getWidth() == 1.1_a);
   REQUIRE(rectangle->getHeight() == 2.2_a);

   auto spacer = makeSpacer(3.3,4.4);
   REQUIRE(spacer->getWidth() == 3.3_a);
   REQUIRE(spacer->getHeight() == 4.4_a);

   auto triangle = makeTriangle(1);
   REQUIRE(triangle->getWidth() == 1.0_a);
   REQUIRE(triangle->getHeight() == Approx(sqrt(3.0)/2.0));

   auto square = makeSquare(1);
   REQUIRE(square->getWidth() == 1.0_a);
   REQUIRE(square->getHeight() == 1.0_a);

   auto hexagon = makePolygon(6,1);
   REQUIRE(hexagon->getWidth() == 2.0_a);
   REQUIRE(hexagon->getHeight() == Approx(sqrt(3.0)));
}

TEST_CASE("Compound Shapes width and height") { //NOLINT
   auto rectangle = makeRectangle(1.1,2.2);
   auto scaledRectangle = makeScaledShape(rectangle,3.3,4.4);
   REQUIRE(scaledRectangle->getWidth() == Approx(1.1*3.3));
   REQUIRE(scaledRectangle->getHeight() == Approx(2.2*4.4));

   auto rotatedRectangle90 = makeRotatedShape(rectangle,Rot::R90);
   REQUIRE(rotatedRectangle90->getWidth() == 2.2_a);
   REQUIRE(rotatedRectangle90->getHeight() == 1.1_a);

   auto rotatedRectangle180 = makeRotatedShape(rectangle,Rot::R180);
   REQUIRE(rotatedRectangle180->getWidth() == 1.1_a);
   REQUIRE(rotatedRectangle180->getHeight() == 2.2_a);

   auto rotatedRectangle270 = makeRotatedShape(rectangle,Rot::R270);
   REQUIRE(rotatedRectangle270->getWidth() == 2.2_a);
   REQUIRE(rotatedRectangle270->getHeight() == 1.1_a);

   auto layeredRectangles = makeLayeredShape({rectangle,rotatedRectangle90});
   REQUIRE(layeredRectangles->getWidth() == 2.2_a);
   REQUIRE(layeredRectangles->getHeight() == 2.2_a);

   auto horizontalRectangles = makeHorizontalShape({rectangle,rotatedRectangle90,rectangle});
   REQUIRE(horizontalRectangles->getWidth() == Approx(1.1+2.2+1.1));
   REQUIRE(horizontalRectangles->getHeight() == 2.2_a);

   auto verticalRectangles = makeVerticalShape({rectangle,rotatedRectangle90,rectangle});
   REQUIRE(verticalRectangles->getWidth() == 2.2_a);
   REQUIRE(verticalRectangles->getHeight() == Approx(2.2+1.1+2.2));
}