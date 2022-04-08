#include <iostream>                //required headers
#include <stdio.h>
#include <vector>
#include <math.h>
#include <cfloat>
#include <cstring>

typedef unsigned char byte;

//defina a struct for 2d point
struct point {
    int x, y;
};


//global variable
std::vector<point> points;

//declaring functions
void merge(int, int, int);
void mergey(int, int, int);


//calculate eculidean distance between points
float dist(point pp1, point pp2)
{
    return sqrt((pp1.x - pp2.x) * (pp1.x - pp2.x) +
        (pp1.y - pp2.y) * (pp1.y - pp2.y)
    );
}


void sort(int start, int end) {

    std::vector<point> set1, set2;

    if (start >= end) {
        //return points;
        return;
    }

    int mid = start + (end - start) / 2;
  
    sort(start, mid);
    sort(mid + 1, end);

    merge(start, mid, end);

}

//sorting by y coordinate
void sorty(int start, int end) {

    std::vector<point> set1, set2;

    if (start >= end) {
        //return points;
        return;
    }

    int mid = start + (end - start) / 2;

    sorty(start, mid);
    sorty(mid + 1, end);

    mergey(start, mid, end);

}


//merging the sorted points in merge sort
void merge(int start, int mid, int end) {

    int const one = mid - start + 1;
    int const two = end - mid;

    std::vector<point> left(one);
    std::vector<point> right(two);

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < one; i++)
        left[i] = points[start + i];
    for (int j = 0; j < two; j++)
        right[j] = points[mid + 1 + j];

    int onei = 0, // Initial index of first sub-array
        twoi = 0; // Initial index of second sub-array
    int mi = start; // Initial index of merged array


    // Merge the temp arrays back into array[left..right]
    while (onei < one && twoi < two) {
        if (left[onei].x <= right[twoi].x) {
            points[mi] = left[onei];
            onei++;
        }
        else {
            points[mi] = right[twoi];
            twoi++;
        }
        mi++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (onei < one) {
        points[mi] = left[onei];
        onei++;
        mi++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (twoi < two) {
        points[mi] = right[twoi];
        twoi++;
        mi++;
    }

    /*for (int i = 0; i < points.size(); i++) {
        std::cout << points[i].x << "\n";
    }*/

    //return points;
}

//merging by y sorting
void mergey(int start, int mid, int end) {
    //std::vector<point> merge(std::vector<point> points, int start, int mid, int end) {
    //std::vector<point> merge(std::vector<point> pts1, std::vector<point> pts2, int start, int mid, int end) {
    //defining two vectors for merging
    //std::vector<point> points(end - start);


    int const one = mid - start + 1;
    int const two = end - mid;

    // Create temp arrays
    //int* left = new std::vector<point>;
    //int* right = new std::vector<point>;
    std::vector<point> left(one);
    std::vector<point> right(two);

    //left = pts1;
    //right = pts2;

    // Copy data to temporary left and right vectors
    for (int i = 0; i < one; i++)
        left[i] = points[start + i];
    for (int j = 0; j < two; j++)
        right[j] = points[mid + 1 + j];

    int onei = 0, twoi = 0; 
    int mi = start; 


    // Merge the temp arrays back into array[left..right]
    while (onei < one && twoi < two) {
        if (left[onei].y <= right[twoi].y) {
            points[mi] = left[onei];
            onei++;
        }
        else {
            points[mi] = right[twoi];
            twoi++;
        }
        mi++;
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (onei < one) {
        points[mi] = left[onei];
        onei++;
        mi++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (twoi < two) {
        points[mi] = right[twoi];
        twoi++;
        mi++;
    }
}


//find the minimum distance
float subclose(std::vector<point> subarr, int size, float d, point &a, point &b)
{
    float min = d;  // Initialize the minimum distance as d

    //point a, b;

    // try all points and calculate difference till d < distance, since y coordinate is in increasing order here and it only contains coordinates
    // with distance < d
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (subarr[j].y - subarr[i].y) < min; ++j)
            if (dist(subarr[i], subarr[j]) < min) {
                min = dist(subarr[i], subarr[j]);
                a = subarr[i];
                b = subarr[j];
            }

    return min;
}


float closest(std::vector<point> Px, std::vector<point> Py, int n, point &a, point &b) {

    //int n = Px.size();
    //if n==1 then different case
    //point a, b;

    point p1, p2, p3, p4;

    if (n < 4) {                                    //not doing this will result in stack overflow during division of points furthur
        float min = FLT_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (dist(Px[i], Px[j]) < min) {
                    min = dist(Px[i], Px[j]);
                    a = Px[i];
                    b = Px[j];
                    //std::cout << min << "   " << a.x << a.y << "   " << b.x << b.y << "\n";
                }
            }
        }   
        return min;
    }


    int mid = n / 2;
    point midpt = Px[mid];

    std::vector<point> Pyl(mid);   // points on one side
    std::vector<point> Pyr(n-mid);  // points on another side
    int li = 0, ri = 0;  // indexes for both
    for (int i = 0; i < n; i++)
    {
        if ((Py[i].x < midpt.x || (Py[i].x == midpt.x && Py[i].y < midpt.y)) && li < mid)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }

    // calculate smallest distance from middle line
    std::vector<point> Px2(Px.begin() + mid, Px.end());
    float left = closest(Px, Pyl, mid, p1, p2);
    float right = closest(Px2, Pyr, n - mid, p3, p4);

    //store the pair of points with smaller distance
    if (left < right) {
        a = p1, b = p2;
    }
    else {
        a = p3, b = p4;
    }

    //find min d
    float d = (left < right) ? left : right;

    // Build an subarray that contains points closer than d
    std::vector<point> subarr(n);
    int j = 0;
    for (int i = 0; i < n; i++)
        if (dist(Py[i], midpt) < d)
            subarr[j] = Py[i], j++;


    //return subclose(subarr, j, d, p1, p2);

    double min = d;
    double temp = subclose(subarr, j, min, p1, p2);
    //std::cout<< "current min" << d << "\n";
    //std::cout<< "next value" << temp << "\n";

    if (temp < d) {
        a = p1, b = p2;

        min = temp;
        
        //std::cout << min << "   " << a.x << a.y << "   " << b.x << b.y << "\n";
    }
    return min;
}

int main() {

    std::vector<point> list;
    std::vector<point> pointsx, pointsy;

    point t;
    t.x = 7;
    t.y = 10;
    list.push_back(t);
    t.x = 38;
    t.y = 59;
    list.push_back(t);
    t.x = 24;       
    t.y = 33;       
    list.push_back(t);
    t.x = 67;       
    t.y = 56;       
    list.push_back(t);
    t.x = 44;       
    t.y = 48;       
    list.push_back(t);
    t.x = 79;       
    t.y = 20;       
    list.push_back(t);
    t.x = 62;       
    t.y = 6;        
    list.push_back(t);
    t.x = 39;       
    t.y = 100;      
    list.push_back(t);
    t.x = 120;
    t.y = 29;
    list.push_back(t);

    //another set but need to set size in list earlier
    /*list[0].x = 7;
    list[0].y = 5;
    list[1].x = 24;
    list[1].y = 33;
    list[2].x = 67;
    list[2].y = 56;
    list[3].x = 44;
    list[3].y = 48;
    list[4].x = 79;
    list[4].y = 20;
    list[5].x = 62;
    list[5].y = 6;
    list[6].x = 39;
    list[6].y = 100;
    list[7].x = 8;
    list[7].y = 10;*/

    std::cout << "Original coordinates" << "\n";
    for (int i = 0; i < list.size(); i++) {
        std::cout << list[i].x << " " << list[i].y << "\n";
    }

    points = list;
    pointsy = list;

    //using emrge sort to sort in x coordinate and sacing in variable pointsx
    sort(0, points.size() - 1);
    //std::cout << points.size();
    pointsx = points;

    points = list;

    //again using mergesort to sort in y coordinate and saving in variable pointsy
    sorty(0, points.size() - 1);
    //std::cout << points.size();
    pointsy = points;

    std::cout << "Sorted by x coordinates" << "\n";
    for (int i = 0; i < pointsx.size(); i++) {
        std::cout << pointsx[i].x << " " << pointsx[i].y << "\n";
    }

    std::cout << "Sorted by y coordinates" << "\n";
    for (int i = 0; i < pointsy.size(); i++) {
        std::cout << pointsy[i].x << " " << pointsy[i].y << "\n";
    }

    //distance and point variables for result
    float min;
    point c, d;

    //min  = closest(pointsx, pointsy, pointsx.size());
    min = closest(pointsx, pointsy, pointsx.size(), c, d);
    //closest(pointsx, pointsy, pointsx.size(), c, d, min);

    std::cout << "Min distance is " << min << "\n";
    std::cout << "Pair of points are " << "(" << c.x << "," << c.y << ") and (" << d.x << "," << d.y << ")";




    //creating image

    int maxx = pointsx[points.size() - 1].x;
    int maxy = pointsy[points.size() - 1].y;

    int max = (maxx > maxy) ? maxx: maxy;
   

    size_t imgsize = 512 * 512 * 3;
    byte* imgdata = (byte*)malloc(imgsize);
    memset(imgdata, 255, imgsize);
    unsigned char pixels[512][512][3];

    //setting the background color for image
    for (unsigned int i = 0; i < 512; i++) {
        for (unsigned int j = 0; j < 512; j++) {
            pixels[j][i][0] = 0;
            pixels[j][i][1] = 0;
            pixels[j][i][2] = 0;
        }
    }
    
    int normx, normy;
    //normalizing the values and then adding it to the pixels
    for (unsigned int i = 0; i < points.size(); i++) {
        normx = 512 * (points[i].x - 12) / ((512 - 12));
        normy = 512 * (points[i].y - 12) / ((512 - 12));

        //color 9 pixels around the point to make it clear
        for (int ii = 0; ii < 3; ii++) {
            for (int jj = 0; jj < 3; jj++)
                pixels[500 - (normx+ii+12)][normy+jj+12][0] = 255;
                
        }

        std::cout << "x value" << normx << "  y value" << normy << "\n";
    }

    //normx = (c.x - 12) / (500 - 12);
    //normy = (c.y - 12) / (500 - 12);
    normx = 512 * (c.x - 12) / (500);
    normy = 512 * (c.y - 12) / (500);

    //color 9 pixels around the point to make it clear
    for (int ii = 0; ii < 3; ii++) {
        for (int jj = 0; jj < 3; jj++)
            pixels[500 - (normx + ii + 12)][normy + jj + 12][1] = 255;

    }

    normx = 512 * (d.x - 12) / (500);
    normy = 512 * (d.y - 12) / (500);

    //color 9 pixels around the point to make it clear
    for (int ii = 0; ii < 3; ii++) {
        for (int jj = 0; jj < 3; jj++)
            pixels[500 - (normx + ii + 12)][normy + jj + 12][1] = 255;

    }

    FILE* image = fopen("hide.ppm", "wb");
    std::fprintf(image, "P6\n%d %d\n%d\n", 512, 512, 255);
    std::fwrite(pixels, 1, 512 * 512 * 3, image);
    std::fclose(image);

}




