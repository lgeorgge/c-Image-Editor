// lgeorgge
// Purpose:Demonstrate use of bmplip for handling bmp grayscale images
//         Program load a gray image and store in another file
#include <bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;
const int Size = 256;
unsigned char image[Size][Size];

// image loading function
void loadFile()
{
    char filename[200];
    cout << "Enter the file name without extension which you want to edit : ";
    cin >> filename;
    strcat(filename, ".bmp");
    readGSBMP(filename, image);
}
// image saving function
void saveFile()
{
    char filename[200];
    cout << "Enter the file name without extension for saving: ";
    cin >> filename;
    strcat(filename, ".bmp");
    writeGSBMP(filename, image);
}
// 1:black and white filter
void black_and_white()
{
    // variable for getting the average of pixels
    int average = 0, sum{}, n{};

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            sum += image[i][j];
            n++;
        }
    }
    average = sum / n;
    // making above average pixels,while below average black
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] > average)
            {
                image[i][j] = 255;
            }
            else
            {
                image[i][j] = 0;
            }
        }
    }
}
// 2:invert filter
void negative()
{

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // inverting the grayscale of pixel
            image[i][j] = 255 - image[i][j];
        }
    }
}
// 3:merge filter
void merge()
{
    // adding another image that will be merged
    unsigned char anotherImage[Size][Size];
    char fileName[200];
    cout << "Enter another Image's Name :";
    cin >> fileName;
    strcat(fileName, ".bmp");
    readGSBMP(fileName, anotherImage);
    // merging by getting the average of grayscale of pixel from the two images
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = (image[i][j] + anotherImage[i][j]) / 2;
        }
    }
}
// 4:flip filter
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
        for (int i = 0; i < Size / 2; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                swap(image[i][j], image[255 - i][j]);
            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE / 2; j++)
            {
                swap(image[i][j], image[i][255 - j]);
            }
        }
    }
}
// 5:rotate filter
void rotate()
{
    // selcting the degree of rotation
    cout << "select orientation 'note that rotations will be anticlock wise' :-\n    1 : 90 degrees\n    2 : 180 degrees\n    3 : 270 degrees" << endl;
    int d;
    cin >> d;
    // using another array of chars to avoid losing pixels while assigning
    unsigned char newimage[Size][Size];
    switch (d)
    {
    case 1:

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                newimage[i][j] = image[j][Size - i];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = newimage[i][j];
            }
        }
        break;
    case 3:
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                newimage[i][j] = image[Size - j][i];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = newimage[i][j];
            }
        }

        break;
    case 2:
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {

                newimage[i][j] = image[Size - i][Size - j];
            }
        }
        for (int i = 0; i < Size - 1; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = newimage[i][j];
            }
        }
        break;

    default:
        break;
    }
}
// 6:darken & lighten
void dark_and_light()
{
    cout << "select ' 1 ' for lightening and ' 2 ' for darkening" << endl;
    int n;
    cin >> n;
    if (n == 1)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = (image[i][j] + 256) / 2;
            }
        }
    }
    else
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j] = (image[i][j] / 2);
            }
        }
    }
}
// 7 : detect image edges
void detect_image_edges()
{

    int average = 0;
    // to get the average of pixels in the image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            average += image[i][j];
        }
    }
    average /= (256 * 256);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (image[i][j] > average && image[i + 1][j] < average || image[i + 1][j] > average && image[i][j + 1] < average || image[i][j + 1] > average && image[i][j] < average || image[i][j + 1] > average && image[i + 1][j] < average || image[i + 1][j] > average && image[i][j] < average || image[i][j] > average && image[i][j + 1] < average)
            {
                image[i][j] = 0;
            }
            else
            {
                image[i][j] = 255;
            }
        }
    }
}
// 8 : enlarge a quarter
void enlarge()
{
    cout << "choose a quarter:-\n    1 : upper left          2 : upper right\n    3 : lower left          4 : lower right" << endl;
    int n;
    cin >> n;
    unsigned char newimage[Size][Size];
    // expanding the pixel among four pixels depending on the input taken from quarter
    switch (n)
    {
    case 1:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                newimage[i * 2][j * 2] = newimage[i * 2 + 1][j * 2] = newimage[i * 2][j * 2 + 1] = newimage[i * 2 + 1][j * 2 + 1] = image[i][j];
            }
        }

        break;
    case 2:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                newimage[i * 2][j * 2] = newimage[i * 2 + 1][j * 2] = newimage[i * 2][j * 2 + 1] = newimage[i * 2 + 1][j * 2 + 1] = image[i][j + 128];
            }
        }

        break;
    case 3:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                newimage[i * 2][j * 2] = newimage[i * 2 + 1][j * 2] = newimage[i * 2][j * 2 + 1] = newimage[i * 2 + 1][j * 2 + 1] = image[i + 128][j];
            }
        }

        break;

    case 4:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                newimage[i * 2][j * 2] = newimage[i * 2 + 1][j * 2] = newimage[i * 2][j * 2 + 1] = newimage[i * 2 + 1][j * 2 + 1] = image[i + 128][j + 128];
            }
        }
        break;

    default:
        break;
    }
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = newimage[i][j];
        }
    }
}
// 9 : shrink according to a scale
void shrink()
{
    cout << "choose shrinking scale : \n    1 : half          2 : third         3 : quarter" << endl;
    int n;
    cin >> n;
    unsigned char newimage[Size][Size];
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
        {
            newimage[i][j] = 255;
        }
    }
    switch (n)
    {
    case 1:

        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                newimage[i][j] = (image[i * 2][j * 2] + image[i * 2 + 1][j * 2] + image[i * 2][j * 2 + 1] + image[i * 2 + 1][j * 2 + 1]) / 4;
            }
        }

        break;
    case 2:
        // since 256 / 3 is about 86
        for (int i = 0; i < 86; i++)
        {
            for (int j = 0; j < 86; j++)
            {
                newimage[i][j] = (image[i * 3][j * 3] + image[i * 3 + 1][j * 3] + image[i * 3][j * 3 + 1] + image[i * 3 + 1][j * 3 + 1] + image[i * 3 + 2][j * 3] + image[i * 3][j * 3 + 2] + image[i * 3 + 2][j * 3 + 2] + image[i * 3 + 1][j * 3 + 2] + image[i * 3 + 2][j * 3 + 1]) / 9;
            }
        }

        break;
    case 3:

        for (int i = 0; i < 64; i++)
        {
            for (int j = 0; j < 64; j++)
            {
                newimage[i][j] = (image[i * 4][j * 4] + image[i * 4 + 1][j * 4] + image[i * 4][j * 4 + 1] + image[i * 4 + 1][j * 4 + 1] + image[i * 4 + 2][j * 4] + image[i * 4][j * 4 + 2] + image[i * 4 + 2][j * 4 + 2] + image[i * 4 + 1][j * 4 + 2] + image[i * 4 + 2][j * 4 + 1] + image[i * 4 + 3][j * 4] + image[i * 4 + 3][j * 4 + 1] + image[i * 4 + 3][j * 4 + 2] + image[i * 4 + 3][j * 4 + 3] + image[i * 4][j * 4 + 3] + image[i * 4 + 1][j * 4 + 3] + image[i * 4 + 2][j * 4 + 3]) / 16;
            }
        }
        break;
    default:
        break;
    }
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = newimage[i][j];
        }
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
            for (int j = 0; j < Size; j++)
            {
                image[255 - i][j] = image[i][j];
            }
        }
        break;
    case 2:
        for (int i = 0; i < 128; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                image[i][j] = image[225 - i][j];
            }
        }
        break;
    case 3:
        for (int i = 0; i < Size; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                image[i][255 - j] = image[i][j];
            }
        }
        break;
    case 4:
        for (int i = 0; i < Size; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                image[i][j] = image[i][255 - j];
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
    unsigned char newimage[Size][Size];

    for (int k = 0; k < 4; k++)
    {
        if (p1 == arr[k].order)
        {
            for (int i = 0; i < 128; i++)
            {
                for (int j = 0; j < 128; j++)
                {
                    newimage[i][j] = image[arr[k].x + i][arr[k].y + j];
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
                    newimage[i][j + 128] = image[arr[k].x + i][arr[k].y + j];
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
                    newimage[i + 128][j] = image[arr[k].x + i][arr[k].y + j];
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
                    newimage[i + 128][j + 128] = image[arr[k].x + i][arr[k].y + j];
                }
            }
            break;
        }
    }

    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = newimage[i][j];
        }
    }
}
// 12 : blur
void blur()
{
    for (int i = 0; i < Size; i += 2)
    {
        for (int j = 0; j < SIZE; j += 2)
        {
            image[i][j + 1] = image[i + 1][j] = image[i][j] = image[i + 1][j + 1] = (image[i][j + 1] + image[i + 1][j] + image[i][j] + image[i + 1][j + 1]) / 4;
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

    unsigned char croppedimage[SIZE][SIZE];

    // clear image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            croppedimage[i][j] = 255;
        }
    }
    // crop the wanted part to the new image
    for (int i = x; i < length; i++)
    {
        for (int j = y; j < width; j++)
        {
            croppedimage[i][j] = image[i][j];
        }
    }
    // put back the cropped part to the original image
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = croppedimage[i][j];
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
    unsigned char newImage[SIZE][SIZE + 256];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE + 256; j++)
            newImage[i][j] = 255;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            newImage[i][j + (int)skeweness] = image[i][j];
        }
        skeweness -= step;
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = 255;
        }
    }
    // shrinking the skewed image and putting it at its original file
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = (newImage[i][j * 2] + newImage[i][j * 2 + 1]) / 2;
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
    unsigned char newImage[SIZE + 256][SIZE];
    for (int i = 0; i < SIZE + 256; i++)
        for (int j = 0; j < SIZE; j++)
            newImage[i][j] = 255;
    for (int j = 0; j < SIZE; j++)
    {
        for (int i = 0; i < SIZE; i++)
        {
            newImage[i + (int)skeweness][j] = image[i][j];
        }
        skeweness -= step;
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = 255;
        }
    }
    // shrinking the skewed image and putting it at its original file
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            image[i][j] = (newImage[i * 2][j] + newImage[i * 2 + 1][j]) / 2;
        }
    }
}

int main()
{
    int selection;
    cin.exceptions(cin.failbit);

    cout << " ________________________________________ Welcome to photo editing program ________________________________________ \n"
         << endl;
    loadFile();
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
            cout << "    14 : skew horizontally" << endl;
            cout << "    15 : skew vertically" << endl;
            cout << "    0 : Exit" << endl;
            cout << "\n      your selection :   ";
            cin >> selection;
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
