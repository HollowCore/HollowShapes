package com.hollowcore.hollowjava.graphic;

import com.hollowcore.hollowjava.geometry.Point;
import com.hollowcore.hollowjava.geometry.Rectangle;

public class Path {
    private long reference = 0;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Definitions
    //----------------------------------------------------------------------------------------------------------------------------------
    public enum Command {
        Move,
        AddLine,
        AddQuadraticCurve,
        AddCubicCurve,
        CloseSubpath,
    }

    public class Element {
        public Command command;
        public Point[] points;
    }

    public interface IntersectionListener {
        boolean intersection(Path path, Path otherPath, Point point);
    }
    public static final double coarseFlatness = 1.01;
    public static final double normalFlatness = 1.001;
    public static final double fineFlatness = 1.0001;

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Construction
    //----------------------------------------------------------------------------------------------------------------------------------
    public Path(String svgPathData) { initNative(svgPathData); }
    private native long initNative(String svgPathData);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Object Polymorphic Functions
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean isEqual(Path other) { return isEqualNative(other); }
    private native boolean isEqualNative(Path other);

    public long hashValue() { return hashNative(); }
    private native long hashNative();

    public String toString() { return toStringNative(); }
    private native String toStringNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Attributes
    //----------------------------------------------------------------------------------------------------------------------------------
    public int getElementCount() { return getElementCountNative(); }
    public native int getElementCountNative();

    public Element getElement(int elementIndex) { return getElementNative(elementIndex); }
    public native Element getElementNative(int elementIndex);

    public Point getCurrentPoint() { return getCurrentPointNative(); }
    public native Point getCurrentPointNative();

    public Rectangle getBounds() { return getBoundsNative(); }
    public native Rectangle getBoundsNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Path Manipulation
    //----------------------------------------------------------------------------------------------------------------------------------
    public void move(double x, double y) { moveNative(x, y); }
    public native void moveNative(double x, double y);

    public void addLine(double x, double y) { addLineNative(x, y); }
    public native void addLineNative(double x, double y);

    public void addQuadraticCurve(double cx, double cy, double x, double y) { addQuadraticCurveNative(cx, cy, x, y); }
    public native void addQuadraticCurveNative(double cx, double cy, double x, double y);

    public void addCubicCurve(double cx0, double cy0, double cx1, double cy1, double x, double y) { addCubicCurveNative(cx0, cy0, cx1, cy1, x, y); }
    public native void addCubicCurveNative(double cx0, double cy0, double cx1, double cy1, double x, double y);

    public void closeSubpath() { closeSubpathNative(); }
    public native void closeSubpathNative();

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Path Conversion
    //----------------------------------------------------------------------------------------------------------------------------------
    public String asSVGPathData() { return asSVGPathDataNative(); }
    public native String asSVGPathDataNative();

    public Point[] asLineSegments(double flatnessThreshold) { return asLineSegmentsNative(flatnessThreshold); }
    public native Point[] asLineSegmentsNative(double flatnessThreshold);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Path Intersection
    //----------------------------------------------------------------------------------------------------------------------------------
    public boolean containsPoint(Point point) { return containsPointNative(point); }
    public native boolean containsPointNative(Point point);

    public boolean containsPointNonZero(Point point) { return containsPointNonZeroNative(point); }
    public native boolean containsPointNonZeroNative(Point point);

    public boolean intersectsPath(Path other) { return intersectsPathNative(other); }
    public native boolean intersectsPathNative(Path other);

    public void intersections(Path other, IntersectionListener intersectionListener) { intersectionsNative(other, intersectionListener); }
    public native void intersectionsNative(Path other, IntersectionListener intersectionListener);

    //----------------------------------------------------------------------------------------------------------------------------------
    // MARK: - Path Evaluation
    //----------------------------------------------------------------------------------------------------------------------------------
//    void HCPathEvaluateLine(HCReal t, HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateQuadraticCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx, HCReal cy, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathEvaluateCubicCurve(HCReal t, HCReal x0, HCReal y0, HCReal cx0, HCReal cy0, HCReal cx1, HCReal cy1, HCReal x1, HCReal y1, HCReal* sx, HCReal* sy, HCReal* dx, HCReal* dy);
//    void HCPathLineLineIntersection(HCReal x0, HCReal y0, HCReal x1, HCReal y1, HCReal x2, HCReal y2, HCReal x3, HCReal y3, HCReal* t, HCReal* u);
}