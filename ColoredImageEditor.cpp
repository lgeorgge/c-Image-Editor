// lgeorgge
//  Purpose:Demonstrate use of bmplip for handling bmp colored images
//          Program load a colored image and store in another file
//          All filters

#include <bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE][RGB];

// image loading function
void loadColoredImage()
{
    char fileName[200];
    cout << "Enter the name of file: ";
    cin >> fileName;
    strcat(fileName, ".bmp");
    readRGBBMP(fileName, image);
}

// image saving function
void saveFile()
{
    char filename[200];
    cout << "Enter the file name without extension for saving: ";
    cin >> filename;
    strcat(filename, ".bmp");
    writeRGBBMP(filename, image);
}

// 1 : black and white
void black_and_white()
{
    // variable for getting the average of pixels
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j][0] = image[i][j][1] = image[i][j][2] = (image[i][j][0] + image[i][j][1] + image[i][j][2]) / 3;
        }
    }
    // making above average pixels WHITE,while below average BLACK
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                if (image[i][j][k] > 127)
                {
                    image[i][j][k] = 255;
                }
                else
                {
                    image[i][j][k] = 0;
                }
            }
        }
    }
}
// 2  :negative
void negative()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
                // inverting the scale of pixel
                image[i][j][k] = 255 - image[i][j][k];
        }
    }
}
// 3 : merge

void merge()
{
    // adding another image that will be merged
    unsigned char anotherImage[SIZE][SIZE][RGB];
    char fileName[200];
    cout << "Enter another Image's Name :";
    cin >> fileName;
    strcat(fileName, ".bmp");
    readRGBBMP(fileName, anotherImage);
    // merging by getting the average of grayscale of pixel from the two images
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                image[i][j][k] = (image[i][j][k] + anotherImage[i][j][k]) / 2;
            }
        }
    }
}

// 4 : flip filter
void flip()
{
    // choosing Vertical or Horizontal
    bool vertical = true;
    cout << "choose alignment:-\n    1 : Horizontal\n    2 : Vertical" << endl;
    int c;
    cin >> c;
    c == 1 ? vertical = false : vertical = true;

    // swapping half of pixels by the other half
    if (vertical)
    {
        for (int i = 0; i < SIZE / 2; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    swap(image[i][j][k], image[255 - i][j][k]);
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                for (int k = 0; k < RGB; k++)
                {

                    swap(image[i][j][k], image[i][255 - j][k]);
                }
            }
        }
    }
}

// 5 : rotate filter
void rotate()
{
    // selcting the degree of rotation
    cout << "select orientation 'note that rotations will be anticlock wise' :-\n    1 : 90 degrees\n    2 : 180 degrees\n    3 : 270 degrees" << endl;
    int d;
    cin >> d;
    // using another array of chars to avoid losing pixels while assigning
    unsigned char newimage[SIZE][SIZE][RGB];
    switch (d)
    {
    case 1:

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {

                    newimage[i][j][k] = image[j][SIZE - i][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }
        break;
    case 3:
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i][j][k] = image[SIZE - j][i][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }

        break;
    case 2:
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {

                    newimage[i][j][k] = image[SIZE - i][SIZE - j][k];
                }
            }
        }
        for (int i = 0; i < SIZE - 1; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }
        break;

    default:
        break;
    }
}

// 6 : darken & lighten filter
void dark_and_light()
{
    cout << "select ' 1 ' for lightening and ' 2 ' for darkening" << endl;
    int n;
    cin >> n;
    if (n == 1)
    {
        // lightening the image
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = (image[i][j][k] + 256) / 2;
                }
            }
        }
    }
    else
    {
        // darkening the image
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image[i][j][k] / 2;
                }
            }
        }
    }
}

// 7 : detect image edges filter
void detect_image_edges()
{

    int average = 0;
    // to get the average of pixels in the image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                average += image[i][j][k];
            }
        }
    }
    average /= (256 * 256 * 3);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                if (image[i][j][k] > average && image[i + 1][j][k] < average ||     // 1
                    image[i + 1][j][k] > average && image[i][j + 1][k] < average || // 2
                    image[i][j + 1][k] > average && image[i][j][k] < average ||     // 3
                    image[i][j + 1][k] > average && image[i + 1][j][k] < average || // 4
                    image[i + 1][j][k] > average && image[i][j][k] < average ||     // 5
                    image[i][j][k] > average && image[i][j + 1][k] < average)       // 6
                {
                    // pixel --> BLACK
                    image[i][j][k] = 0;
                }
                else
                {
                    // pixel --> WHITE
                    image[i][j][k] = 255;
                }
            }
        }
    }
    black_and_white();
}

// 8: enlarge filter

void enlarge()
{
    cout << "choose a quarter:-\n    1 : upper left          2 : upper right\n    3 : lower left          4 : lower right" << endl;
    int n;
    cin >> n;
    unsigned char newimage[SIZE][SIZE][RGB];

    // expanding the pixel among four pixels depending on the input taken from quarter
    switch (n)
    {
    case 1:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i * 2][j * 2][k] = newimage[i * 2 + 1][j * 2][k] = newimage[i * 2][j * 2 + 1][k] = newimage[i * 2 + 1][j * 2 + 1][k] = image[i][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }

        break;
    case 2:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                for (int k = 0; k < RGB; k++)
                {

                    newimage[i * 2][j * 2][k] = newimage[i * 2 + 1][j * 2][k] = newimage[i * 2][j * 2 + 1][k] = newimage[i * 2 + 1][j * 2 + 1][k] = image[i][j + 128][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }
        break;
    case 3:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i * 2][j * 2][k] = newimage[i * 2 + 1][j * 2][k] = newimage[i * 2][j * 2 + 1][k] = newimage[i * 2 + 1][j * 2 + 1][k] = image[i + 128][j][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }

        break;

    case 4:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i * 2][j * 2][k] = newimage[i * 2 + 1][j * 2][k] = newimage[i * 2][j * 2 + 1][k] = newimage[i * 2 + 1][j * 2 + 1][k] = image[i + 128][j + 128][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }

        break;

    default:
        break;
    }
}

// 9 : shrinking filter
void shrink()
{
    cout << "choose shronking scale : \n    1 : half          2 : third         3 : quarter" << endl;
    int n;
    cin >> n;
    unsigned char newimage[SIZE][SIZE][RGB];
    switch (n)
    {
    case 1:
        // clearing the new image --> white background
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i][j][k] = 255;
                }
            }
        }
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i][j][k] = (image[i * 2][j * 2][k] + image[i * 2 + 1][j * 2][k] + image[i * 2][j * 2 + 1][k] + image[i * 2 + 1][j * 2 + 1][k]) / 4;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }

        break;
    case 2:
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i][j][k] = 255;
                }
            }
        }
        for (int i = 0; i < 86; i++)
        {
            for (int j = 0; j < 86; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i][j][k] = (image[i * 3][j * 3][k] + image[i * 3 + 1][j * 3][k] + image[i * 3][j * 3 + 1][k] + image[i * 3 + 1][j * 3 + 1][k] + image[i * 3 + 2][j * 3][k] + image[i * 3][j * 3 + 2][k] + image[i * 3 + 2][j * 3 + 2][k] + image[i * 3 + 1][j * 3 + 2][k] + image[i * 3 + 2][j * 3 + 1][k]) / 9;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }

        break;
    case 3:
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i][j][k] = 255;
                }
            }
        }
        for (int i = 0; i < 64; i++)
        {
            for (int j = 0; j < 64; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    newimage[i][j][k] = (image[i * 4][j * 4][k] + image[i * 4 + 1][j * 4][k] + image[i * 4][j * 4 + 1][k] + image[i * 4 + 1][j * 4 + 1][k] + image[i * 4 + 2][j * 4][k] + image[i * 4][j * 4 + 2][k] + image[i * 4 + 2][j * 4 + 2][k] + image[i * 4 + 1][j * 4 + 2][k] + image[i * 4 + 2][j * 4 + 1][k] + image[i * 4 + 3][j * 4][k] + image[i * 4 + 3][j * 4 + 1][k] + image[i * 4 + 3][j * 4 + 2][k] + image[i * 4 + 3][j * 4 + 3][k] + image[i * 4][j * 4 + 3][k] + image[i * 4 + 1][j * 4 + 3][k] + image[i * 4 + 2][j * 4 + 3][k]) / 16;
                }
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = newimage[i][j][k];
                }
            }
        }

        break;

    default:
        break;
    }
}
// 10 : mirror
void mirror()
{
    // mirroring only one half of any orientation
    cout << "choose the part you want to mirror :\n    1 : upper part               2 : lower part\n    3 : left part                4 : right part" << endl;
    int n;
    cin >> n;
    switch (n)
    {
    case 1:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[255 - i][j][k] = image[i][j][k];
                }
            }
        }
        break;
    case 2:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image[225 - i][j][k];
                }
            }
        }
        break;
    case 3:
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][255 - j][k] = image[i][j][k];
                }
            }
        }
        break;
    case 4:
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                for (int k = 0; k < RGB; k++)
                {
                    image[i][j][k] = image[i][255 - j][k];
                }
            }
        }
        break;

    default:
        break;
    }
}

// 11 : shuffle
void shuffle()
{
    // making partitions to increase efficiency during rearranging the pexils
    struct part
    {
        int order, x, y;
    };
    part first;
    first.order = 1;
    first.x = 0;
    first.y = 0;
    part second;
    second.order = 2;
    second.x = 0;
    second.y = 127;
    part third;
    third.order = 3;
    third.x = 127;
    third.y = 0;
    part fourth;
    fourth.order = 4;
    fourth.x = 127;
    fourth.y = 127;
    vector<part> arr = {first, second, third, fourth};
    int p1, p2, p3, p4;

    // handling exception
    cin.exceptions(cin.failbit);
    try
    {
        cout << "choose the new order by adding four numbers range from 1 to 4 with spaces : " << endl;
        cin >> p1 >> p2 >> p3 >> p4;
        if ((p1 < 1 || p1 > 5) || (p2 < 1 || p2 > 5) || (p3 < 1 || p3 > 5) || (p4 < 1 || p4 > 5))
        {
            throw "You entered wrong input";
        }
    }
    catch (const char *error)
    {
        cerr << error << endl;
    }
    // making 4 loops,each handle a specific quarter according to the users selection
    unsigned char newimage[SIZE][SIZE][RGB];

    for (int k = 0; k < 4; k++)
    {
        if (p1 == arr[k].order)
        {
            for (int i = 0; i < 128; i++)
            {
                for (int j = 0; j < 128; j++)
                {
                    for (int w = 0; w < RGB; w++)
                    {

                        newimage[i][j][w] = image[arr[k].x + i][arr[k].y + j][w];
                    }
                }
            }
            break;
        }
    }
    for (int k = 0; k < 4; k++)
    {
        if (p2 == arr[k].order)
        {
            for (int i = 0; i < 128; i++)
            {
                for (int j = 0; j < 128; j++)
                {
                    for (int w = 0; w < RGB; w++)
                    {
                        newimage[i][j + 128][w] = image[arr[k].x + i][arr[k].y + j][w];
                    }
                }
            }
            break;
        }
    }
    for (int k = 0; k < 4; k++)
    {
        if (p3 == arr[k].order)
        {
            for (int i = 0; i < 128; i++)
            {
                for (int j = 0; j < 128; j++)
                {
                    for (int w = 0; w < RGB; w++)
                    {
                        newimage[i + 128][j][w] = image[arr[k].x + i][arr[k].y + j][w];
                    }
                }
            }
            break;
        }
    }
    for (int k = 0; k < 4; k++)
    {
        if (p4 == arr[k].order)
        {
            for (int i = 0; i < 128; i++)
            {
                for (int j = 0; j < 128; j++)
                {
                    for (int w = 0; w < RGB; w++)
                    {
                        newimage[i + 128][j + 128][w] = image[arr[k].x + i][arr[k].y + j][w];
                    }
                }
            }
            break;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                image[i][j][k] = newimage[i][j][k];
            }
        }
    }
}

// 12 : blur filter
void blur()
{
    for (int i = 0; i < SIZE; i += 2)
    {
        for (int j = 0; j < SIZE; j += 2)
        {
            for (int k = 0; k < RGB; k++)
            {
                image[i][j + 1][k] = image[i + 1][j][k] = image[i][j][k] = image[i + 1][j + 1][k] = (image[i][j + 1][k] + image[i + 1][j][k] + image[i][j][k] + image[i + 1][j + 1][k]) / 4;
            }
        }
    }
}

// 13 : crop
void crop()
{
    int length, width, x, y;
    cout << "Enter the coordinates of the length 'range from 0 to 255':  ";
    cin >> x >> length;
    cout << "Enter the coordinates of the width 'range from 0 to 255':  ";
    cin >> y >> width;

    unsigned char croppedimage[SIZE][SIZE][RGB];

    // clear image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int l = 0; l < RGB; l++)
            {
                croppedimage[i][j][l] = 255;
            }
        }
    }
    // crop the wanted part to the new image
    for (int i = x; i < length; i++)
    {
        for (int j = y; j < width; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                croppedimage[i][j][k] = image[i][j][k];
            }
        }
    }
    // put back the cropped part to the original image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                image[i][j][k] = croppedimage[i][j][k];
            }
        }
    }
}
// skew horizontally
void skew_horizontally()
{
    double angle;
    cout << "Enter the degree of skewness (between 0 and 45) : ";
    cout << endl;
    cin >> angle;
    // taking angle in radian system
    angle *= 3.14 / 180;
    double skeweness = tan(angle) * 256;
    double step = skeweness / SIZE;
    // making a new double-sized in width array to hold as much pixels as possible(worst case)
    unsigned char newImage[SIZE][SIZE + 256][RGB];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE + 256; j++)
            for (int k = 0; k < RGB; k++)
                newImage[i][j][k] = 255;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                newImage[i][j + (int)skeweness][k] = image[i][j][k];
            }
        }
        skeweness -= step;
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                image[i][j][k] = 255;
            }
        }
    }
    // shrinking the skewed image and putting it at its original file
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                image[i][j][k] = (newImage[i][j * 2][k] + newImage[i][j * 2 + 1][k]) / 2;
            }
        }
    }
}

// skew vertically
void skew_vertically()
{
    double angle;
    cout << "Enter the degree of skewness (between 0 and 45) : ";
    cin >> angle;
    cout << endl;
    angle *= 3.14 / 180;
    double skeweness = tan(angle) * 256;
    double step = skeweness / SIZE;
    // making a new double-sized in columns array to hold as much pixels as possible(worst case)
    unsigned char newImage[SIZE + 256][SIZE][RGB];
    for (int i = 0; i < SIZE + 256; i++)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < RGB; k++)
                newImage[i][j][k] = 255;
    for (int j = 0; j < SIZE; j++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int k = 0; k < RGB; k++)
            {
                newImage[i + (int)skeweness][j][k] = image[i][j][k];
            }
        }
        skeweness -= step;
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                image[i][j][k] = 255;
            }
        }
    }
    // shrinking the skewed image and putting it at its original file
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                image[i][j][k] = (newImage[i * 2][j][k] + newImage[i * 2 + 1][j][k]) / 2;
            }
        }
    }
}

int main()
{
    int selection;
    cin.exceptions(cin.failbit);

    cout << " ________________________________________ Welcome to photo editing program ________________________________________ \n"
         << endl;
    loadColoredImage();
    // making sure the user enters a right number
    bool isWrongValue = true;
    while (isWrongValue)
    {
        try
        {
            cout << "select the filter you want to implement, or ' 0 ' to exit : \n"
                 << endl;
            cout << "    1 : black & white filter" << endl;
            cout << "    2 : invert filter" << endl;
            cout << "    3 : merging two images" << endl;
            cout << "    4 : flip image (Vertically or Horizontally)" << endl;
            cout << "    5 : rotating image" << endl;
            cout << "    6 : darkening & whitening the image" << endl;
            cout << "    7 : detect image edges" << endl;
            cout << "    8 : enlarge a specific quarter" << endl;
            cout << "    9 : shring according to a scale" << endl;
            cout << "    10 : mirror " << endl;
            cout << "    11 : shuffle " << endl;
            cout << "    12 : blur" << endl;
            cout << "    13 : crop  " << endl;
            cout << "    14 : skew horizontally " << endl;
            cout << "    15 : skew vertically" << endl;
            cout << "    0 : Exit" << endl;
            cout << "\n      your selection :  ";
            cin >> selection;
            cout << endl;
            if (selection < 0 || selection > 15)
                throw "error";
            isWrongValue = false;
        }
        catch (char const *error)
        {
            cerr << "your selection is unavaible,please select a number from the list " << endl;
        };
    }
    switch (selection)
    {
    case 1:
        black_and_white();
        break;
    case 2:
        negative();
        break;
    case 3:
        merge();
        break;
    case 4:
        flip();
        break;
    case 5:
        rotate();
        break;
    case 6:
        dark_and_light();
        break;
    case 7:
        detect_image_edges();
        break;
    case 8:
        enlarge();
        break;
    case 9:
        shrink();
        break;
    case 10:
        mirror();
        break;
    case 11:
        shuffle();
        break;
    case 12:
        blur();
        break;
    case 13:
        crop();
        break;
    case 14:
        skew_horizontally();
        break;
    case 15:
        skew_vertically();
        break;
    default:
        break;
    }

    saveFile();
}
