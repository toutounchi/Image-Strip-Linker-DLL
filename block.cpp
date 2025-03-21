#include "block.h"
#include <cmath>
#include <iostream>

int Block::Height() const
{
    if (!data.empty())
    {
        return data[0].size();
    }
    return 0;
}

int Block::Width() const
{
    // To prevent the seg fault in case of an emty vector
    return data.size();
}

void Block::Render(PNG &im, int x) const
{
    for (int i = 0; i < Height(); i++)
    {
        for (int j = 0; j < Width(); j++)
        {
            // *im.getPixel(x+j,i) = data[i][j];
            RGBAPixel *pixel = im.getPixel(x + j, i);
            pixel->r = data[j][i].r;
            pixel->g = data[j][i].g;
            pixel->b = data[j][i].b;
            pixel->a = data[j][i].a;
        }
    }
}

void Block::Build(PNG &im, int x, int width)
{
    // Extending the vector to fit the block of pixels
    // vector[height][width]
    data.resize(width, vector<RGBAPixel>(im.height()));

    for (int i = 0; i < im.height(); i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBAPixel *pixel = im.getPixel(x + j, i);
            data[j][i].r = pixel->r;
            data[j][i].g = pixel->g;
            data[j][i].b = pixel->b;
            data[j][i].a = pixel->a;
        }
    }
}
