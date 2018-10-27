#include "constants.h"

void renderPixel(int orig_x, int orig_y, float r, float g, float b) {
    glBegin(GL_POINTS);
        glColor3f(r, g, b);
        float ox = (double)orig_x/(FRAME_W/2) - 1;
        float oy = -((double)orig_y/(FRAME_H/2) - 1);
        glVertex2f(ox, oy);
    glEnd();
} 

void setPixel4(int cx, int cy, int R, float r, float g, float b) {
    renderPixel(cx, cy + R, r, g, b);
    renderPixel(cx, cy - R, r, g, b);
    renderPixel(cx + R, cy, r, g, b);
    renderPixel(cx - R, cy, r, g, b);
}

void setPixel8(int cx, int cy, int x, int y, float r, float g, float b) {
    renderPixel(cx + x, cy + y, r, g, b);
    renderPixel(cx - x, cy + y, r, g, b);
    renderPixel(cx + x, cy - y, r, g, b);
    renderPixel(cx - x, cy - y, r, g, b);
    renderPixel(cx + y, cy + x, r, g, b);
    renderPixel(cx - y, cy + x, r, g, b);
    renderPixel(cx + y, cy - x, r, g, b);
    renderPixel(cx - y, cy - x, r, g, b);
}

void drawCircle(int cx, int cy, int R, float r, float g, float b) {
    setPixel4(cx, cy, R, r, g, b);
    int x = 0;
    int y = R;
    int f = 1 - R;
    int incrE = 3;
    int incrSE = 5 - 2 * R;
    while (x <= y) {
        x++;
        if (f > 0) {
            y = y - 1;
            f += incrSE;
            incrSE += 4;
        } else {
            f += incrE;
            incrSE += 2;
        }
        incrE += 2;
        setPixel8(cx, cy, x, y, r, g, b);
    }
}

void currentPixelColor(int x, int y, float& r, float& g, float& b) {
    GLfloat pixel_color[3];
    int oy = FRAME_W - y;
    glReadPixels(x, oy, 1, 1, GL_RGB, GL_FLOAT , &pixel_color[0]);
    r = pixel_color[0];
    g = pixel_color[1];
    b = pixel_color[2];
}

bool isOffScreen(int x, int y) {
    return (x < 1 || x + 1 >= FRAME_W) || (y < 1 || y + 1 >= FRAME_W);
}

bool couldFill(int x, int y, float r, float g, float b, float rr, float gg, float bb) {
    if (isOffScreen(x, y)) {
        return false;
    }
    float rrr;
    float ggg;
    float bbb;

    currentPixelColor(x, y, rrr, ggg, bbb);
    bool res = (r != rrr || g != ggg || b != bbb) && (rr == rrr && gg == ggg && bb == bbb);
    //printf("%d %d %g %g %g %g %g %g %g %g %g %s\n", x, y, rrr, ggg, bbb, rr, gg, bb, r, g, b, res ? "true" : "false");
    return res;
}

void innerFlood(int x, int y, float r, float g, float b, float rr, float gg, float bb) {
    //sleep(1);
    if (isOffScreen(x, y)) {
        return;
    }
    renderPixel(x, y, r, g, b);
    if (couldFill(x + 1, y, r, g, b, rr, gg, bb)) {
        innerFlood(x + 1, y, r, g, b, rr, gg, bb);
    }
    if (couldFill(x - 1, y, r, g, b, rr, gg, bb)) {
        innerFlood(x - 1, y, r, g, b, rr, gg, bb);
    }
    if (couldFill(x, y + 1, r, g, b, rr, gg, bb)) {
        innerFlood(x, y + 1, r, g, b, rr, gg, bb);
    }
    if (couldFill(x, y - 1, r, g, b, rr, gg, bb)) {
        innerFlood(x, y - 1, r, g, b, rr, gg, bb);
    }
}

void FloodFill(int x, int y, float r, float g, float b) {
    if (isOffScreen(x, y)) {
        return;
    }
    float rr = 0.0;
    float gg = 0.0; 
    float bb = 0.0;
    currentPixelColor(x, y, rr, gg, bb);
    printf("%g %g %g\n", rr, gg, bb);

    
    if (r != rr || g != gg || b != bb) {
        renderPixel(x, y, r, g, b);
    } else {
        return;
    }

    if (couldFill(x + 1, y, r, g, b, rr, gg, bb)) {
        innerFlood(x + 1, y, r, g, b, rr, gg, bb);
    }
    if (couldFill(x - 1, y, r, g, b, rr, gg, bb)) {
        innerFlood(x - 1, y, r, g, b, rr, gg, bb);
    }
    if (couldFill(x, y + 1, r, g, b, rr, gg, bb)) {
        innerFlood(x, y + 1, r, g, b, rr, gg, bb);
    }
    if (couldFill(x, y - 1, r, g, b, rr, gg, bb)) {
        innerFlood(x, y - 1, r, g, b, rr, gg, bb);
    }
}

void drawLine(int x1, int y1, int x2, int y2, float r, float g, float b) {
    float slope = ((y2 - y1) << 16) / (x2 - x1);
    int x = x1;
    int y = y1 << 16;
    int count = x2 - x1;
    if (count < 0) count *= -1;
    renderPixel(x1, y1, r, g, b);
    renderPixel(x1+1, y1, r, g, b);
    renderPixel(x1-1, y1, r, g, b);
    renderPixel(x1, y1+1, r, g, b);
    renderPixel(x1, y1-1, r, g, b);
    while (count > 0) {
        count -= 1;
        y = x1 < x2 ? y + slope : y - slope;
        x = x1 < x2 ? x+1 : x-1;
        renderPixel(x, y >> 16, r, g, b);
        renderPixel(x+1, y >> 16, r, g, b);
        renderPixel(x-1, (y >> 16) +1, r, g, b);
        renderPixel(x, (y >> 16) - 1, r, g, b);
    }
}