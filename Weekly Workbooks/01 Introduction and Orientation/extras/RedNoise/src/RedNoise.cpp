#include <CanvasTriangle.h>
#include <DrawingWindow.h>
#include <Utils.h>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <CanvasPoint.h>
#include <Colour.h>
#include <algorithm>
#include "TextureMap.h"


#define WIDTH 320
#define HEIGHT 240


/*std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues) {
    float step = (to - from) / (numberOfValues - 1);
    std::vector<float> values(numberOfValues);
    for (int i = 0; i < numberOfValues; i++) {
        values[i] = from + step * i;
    }
    return values;
}*/

/*void draw(DrawingWindow &window) {
	window.clearPixels();
	for (size_t y = 0; y < window.height; y++) {
		for (size_t x = 0; x < window.width; x++) {
			float red = rand() % 256;
			float green = 0.0;
			float blue = 0.0;
			uint32_t colour = (255 << 24) + (int(red) << 16) + (int(green) << 8) + int(blue);
			window.setPixelColour(x, y, colour);
		}
	}
}*/
/*void draw(DrawingWindow &window) {
    window.clearPixels();
    // from 255 to 0 mean Gradient from wight to black
    std::vector<float> gradient = interpolateSingleFloats(255, 0, window.width);
    for (size_t y = 0; y < window.height; y++) {
        for (size_t x = 0; x < window.width; x++) {
            // red = green = blue mean Grayscale
            float red ;
            float green;
            float blue;
            red=green=blue= static_cast<uint8_t>(gradient[x]);
            uint32_t colour = (255 << 24) + (int(red) << 16) + (int(green) << 8) + int(blue);
            window.setPixelColour(x, y, colour);
        }
    }
}*/

/*std::vector<glm::vec3> interpolateThreeElementValues(glm::vec3 from, glm::vec3 to, int numberOfValues) {
    std::vector<glm::vec3> interpolatedValues;
    if (numberOfValues <= 1) return interpolatedValues;  // Edge case
    glm::vec3 step = (to - from) / float(numberOfValues - 1);
    for (int i = 0; i < numberOfValues; i++) {
        interpolatedValues.push_back(from + step * float(i));
    }
    return interpolatedValues;
}*/
/*void draw(DrawingWindow &window) {
    window.clearPixels();
    //A good way to tackle this problem is to start by creating variables for the four corners of the window and initialising them with the following primary colours:
    glm::vec3 topLeft(255, 0, 0);        // red
    glm::vec3 topRight(0, 0, 255);       // blue
    glm::vec3 bottomRight(0, 255, 0);    // green
    glm::vec3 bottomLeft(255, 255, 0);   // yellow
    //Calculate the colour of all the pixels in the first (left-most) column of the window
    std::vector<glm::vec3> leftColors = interpolateThreeElementValues(topLeft, bottomLeft, window.height);
    //Calculate the colour of all the pixels in the first (left-most) column of the window
    std::vector<glm::vec3> rightColors = interpolateThreeElementValues(topRight, bottomRight, window.height);
    for (size_t y = 0; y < window.height; y++) {
       // Calculate the colour of all the pixels in the first (left-most) column of the window
        std::vector<glm::vec3> rowColors = interpolateThreeElementValues(leftColors[y], rightColors[y], window.width);
       // std::vector<glm::vec3> rowColors = interpolateThreeElementValues(rightColors[y], leftColors[y], window.width);
        for (size_t x = 0; x < window.width; x++) {
            float red =rowColors[x].r;
            float green= rowColors[x].g;
            float blue= rowColors[x].b;
            uint32_t colour = (255 << 24) + (int(red) << 16) + (int(green) << 8) + int(blue);
            window.setPixelColour(x, y, colour);
        }
    }
}*/





//int main(int argc, char *argv[]) {
   // std::vector<float> result;
    // result = interpolateSingleFloats(2.2, 8.5, 7);
   // for(size_t i=0; i<result.size(); i++)
   //     std::cout << result[i] << " ";
    // std::cout << std::endl;

   // glm::vec3 from(1.0, 4.0, 9.2);
   // glm::vec3 to(4.0, 1.0, 9.8);
   // std::vector<glm::vec3> results = interpolateThreeElementValues(from, to, 4);
   // for (glm::vec3 vec : results) {
    //    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
    //  }


	//DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	//SDL_Event event;
	//while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		//if (window.pollForInputEvents(event)) handleEvent(event, window);
		//draw(window);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		//window.renderFrame();
	//}
//}


//画线
void drawLine(DrawingWindow &window, const CanvasPoint &p1, const CanvasPoint &p2, const Colour &color) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps = std::max(abs(dx), abs(dy));
    float xInc = static_cast<float>(dx) / steps;
    float yInc = static_cast<float>(dy) / steps;
    float x = p1.x;
    float y = p1.y;

    uint32_t pixelColor = (255 << 24) + (color.red << 16) + (color.green << 8) + color.blue;

    for (int i = 0; i <= steps; i++) {
        window.setPixelColour(round(x), round(y), pixelColor);
        x += xInc;
        y += yInc;
    }
}

//画三角 draw a triangle   window name,
void drawTriangle(DrawingWindow &window, const CanvasTriangle &triangle, const Colour &color) {
    drawLine(window, triangle.vertices[0], triangle.vertices[1], color);
    drawLine(window, triangle.vertices[1], triangle.vertices[2], color);
    drawLine(window, triangle.vertices[0], triangle.vertices[2], color);
}


void drawTexturedLine(DrawingWindow &window, const CanvasPoint &start, const CanvasPoint &end, const TextureMap &texture) {
//    int steps = std::max(abs(end.x - start.x), abs(end.y - start.y));

//    float xStep = (end.x - start.x) / steps;
//    float yStep = (end.y - start.y) / steps;


    float deltaX = abs(end.x - start.x);
    float deltaY = abs(end.y - start.y);
    int steps = std::max(deltaX, deltaY);
    float xStep = deltaX / steps;
    float yStep = deltaY / steps;
    float uStep = (end.texturePoint.x - start.texturePoint.x) / steps;
    float vStep = (end.texturePoint.y - start.texturePoint.y) / steps;

    float x = start.x;
    float y = start.y;
    float u = start.texturePoint.x;
    float v = start.texturePoint.y;


    for (int i = 0; i <= steps; i++) {
        if (u < 0 || u >= texture.width || v < 0 || v >= texture.height) {
            std::cerr << "Texture coordinates out of bounds: u = " << u << ", v = " << v << std::endl;
            continue;
        }
        if (u >= 0 && u < texture.width && v >= 0 && v < texture.height) {
            uint32_t color = texture.pixels[int(v) * texture.width + int(u)];
            window.setPixelColour(round(x), round(y), color);
        } else {
            // 处理坐标(u, v)超出纹理范围的情况，例如设置为默认颜色
            window.setPixelColour(round(x), round(y), 0);
        }

        x += xStep;
        y += yStep;
        u += uStep;
        v += vStep;
    }



}

//填图 fill the triangle
void fillTriangle(DrawingWindow &window, const CanvasTriangle &triangle, const Colour &color) {
    std::array<CanvasPoint, 3> sortedVertices = {triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]};
    std::sort(sortedVertices.begin(), sortedVertices.end(), [](const CanvasPoint &a, const CanvasPoint &b) -> bool {
        return a.y < b.y;
    });

    auto computeIntersection = [](const CanvasPoint &a, const CanvasPoint &b, float y) -> float {
        if (a.y == b.y) return a.x;
        return a.x + (b.x - a.x) * (y - a.y) / (b.y - a.y);
    };

    for (int y = static_cast<int>(sortedVertices[0].y); y < static_cast<int>(sortedVertices[1].y); y++) {
        int startX = computeIntersection(sortedVertices[0], sortedVertices[2], y);
        int endX = computeIntersection(sortedVertices[0], sortedVertices[1], y);
        drawLine(window, CanvasPoint(startX, y), CanvasPoint(endX, y), color);
    }

    for (int y = static_cast<int>(sortedVertices[1].y); y <= static_cast<int>(sortedVertices[2].y); y++) {
        int startX = computeIntersection(sortedVertices[0], sortedVertices[2], y);
        int endX = computeIntersection(sortedVertices[1], sortedVertices[2], y);
        drawLine(window, CanvasPoint(startX, y), CanvasPoint(endX, y), color);
    }
}

std::array<CanvasPoint, 3> getSortedVertices(const CanvasTriangle &triangle) {
    std::array<CanvasPoint, 3> sortedVertices = {triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]};
    std::sort(sortedVertices.begin(), sortedVertices.end(), [](const CanvasPoint &a, const CanvasPoint &b) -> bool {
        return a.y < b.y;
    });
    return sortedVertices;
}


void fillTexturedTriangle(DrawingWindow &window, const CanvasTriangle &triangle, const TextureMap &texture) {
    std::array<CanvasPoint, 3> sortedVertices = getSortedVertices(triangle);

    auto computeIntersection = [](const CanvasPoint &a, const CanvasPoint &b, float y) -> CanvasPoint {
        float alpha = (y - a.y) / (b.y - a.y);
        float x = a.x + alpha * (b.x - a.x);
        float u = a.texturePoint.x + alpha * (b.texturePoint.x - a.texturePoint.x);
        float v = a.texturePoint.y + alpha * (b.texturePoint.y - a.texturePoint.y);

        CanvasPoint resultPoint(x, y);
        resultPoint.texturePoint = TexturePoint(u, v);

        return resultPoint;
    };


    for (int y = static_cast<int>(sortedVertices[0].y); y < static_cast<int>(sortedVertices[1].y); y++) {
        CanvasPoint start = computeIntersection(sortedVertices[0], sortedVertices[2], y);
        CanvasPoint end = computeIntersection(sortedVertices[0], sortedVertices[1], y);

        // 检查并交换 start 和 end，确保 start 在左边
        if(start.x > end.x) {
            std::swap(start, end);
        }

        drawTexturedLine(window, start, end, texture);
    }

    for (int y = static_cast<int>(sortedVertices[1].y); y <= static_cast<int>(sortedVertices[2].y); y++) {
        CanvasPoint start = computeIntersection(sortedVertices[0], sortedVertices[2], y);
        CanvasPoint end = computeIntersection(sortedVertices[1], sortedVertices[2], y);

        // 同样，检查并交换 start 和 end
        if(start.x > end.x) {
            std::swap(start, end);
        }

        drawTexturedLine(window, start, end, texture);
    }

//    for (int y = static_cast<int>(sortedVertices[1].y); y <= static_cast<int>(sortedVertices[2].y); y++) {
//        CanvasPoint start = computeIntersection(sortedVertices[0], sortedVertices[2],y );
//        drawDebugPoint(window, start);
//        CanvasPoint end = computeIntersection(sortedVertices[1], sortedVertices[2], y);
//        drawDebugPoint(window, end);
//        drawTexturedLine(window, start, end, texture);
//
//    }


}


void handleEvent(SDL_Event event, DrawingWindow &window) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT) std::cout << "LEFT" << std::endl;
        else if (event.key.keysym.sym == SDLK_RIGHT) std::cout << "RIGHT" << std::endl;
        else if (event.key.keysym.sym == SDLK_UP) std::cout << "UP" << std::endl;
        else if (event.key.keysym.sym == SDLK_DOWN) std::cout << "DOWN" << std::endl;
        else if (event.key.keysym.sym == SDLK_f) {
            // Generate three random vertices
//            CanvasPoint p1(rand() % window.width, rand() % window.height);
//            CanvasPoint p2(rand() % window.width, rand() % window.height);
//            CanvasPoint p3(rand() % window.width, rand() % window.height);

                CanvasPoint p1(160, 10);
        p1.texturePoint = TexturePoint(195, 5);
        CanvasPoint p2(300, 230);
        p2.texturePoint = TexturePoint(395, 380);
        CanvasPoint p3(10, 150);
        p3.texturePoint = TexturePoint(65, 330);
        // 创建三角形
        CanvasTriangle triangle(p1, p2, p3);

            // Generate a random color
            Colour randomColor(rand() % 256, rand() % 256, rand() % 256);
            fillTriangle(window, triangle, randomColor);
            // Draw the triangle
            Colour whiteColor(255, 255, 255);
            drawTriangle(window, triangle, whiteColor);
        }
        else if (event.key.keysym.sym == SDLK_u) {
            CanvasPoint p1(rand() % window.width, rand() % window.height);
            CanvasPoint p2(rand() % window.width, rand() % window.height);
            CanvasPoint p3(rand() % window.width, rand() % window.height);
            CanvasTriangle triangle(p1, p2, p3);
            Colour randomColor(rand() % 256, rand() % 256, rand() % 256);
            drawTriangle(window, triangle, randomColor);
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        window.savePPM("output.ppm");
        window.saveBMP("output.bmp");
    }
}




int main() {
    // 初始化窗口
    DrawingWindow window(1200, 600, false);  // 假设您的窗口大小为800x600
    // 加载纹理
    TextureMap texture("/home/merlin/CG2023/Weekly Workbooks/03 Triangles and Textures/texture.ppm");
    // 设置CanvasPoint和对应的TexturePoint
    CanvasPoint p1(160, 10);
    p1.texturePoint = TexturePoint(195, 5);
    CanvasPoint p2(300, 230);
    p2.texturePoint = TexturePoint(395, 380);
    CanvasPoint p3(10, 150);
    p3.texturePoint = TexturePoint(65, 330);
    // 创建三角形
    CanvasTriangle triangle(p1, p2, p3);
    // 清空窗口 (假设黑色背景)
    window.clearPixels();
    // 填充三角形
    fillTexturedTriangle(window, triangle, texture);



    // 渲染
    window.renderFrame();

    // 事件循环，等待窗口关闭
    bool running = true;
    while (running) {
        SDL_Event event;
        while (window.pollForInputEvents(event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            // 其他事件处理，如键盘、鼠标等
            handleEvent(event, window);
        }
    }

    return 0;
}





//int main(int argc, char* argv[]) {
//    DrawingWindow window = DrawingWindow(800, 600, false);
//    bool running = true;
//    while (running) {
//        SDL_Event event;
//        while (window.pollForInputEvents(event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            } else {
//                handleEvent(event, window);
//            }
//        }
//        window.renderFrame();
//    }
//    return 0;
//}


//week3-1
//int main(int argc, char* argv[]) {
//    DrawingWindow window = DrawingWindow(800, 600, false);
//    bool running = true;
//    while (running) {
//        SDL_Event event;
//        while (window.pollForInputEvents((event)) ){ // This is correct now
//            if (event.type == SDL_QUIT) running = false;
//        }
//        Colour white(255, 255, 255);  // Define white color
//        window.clearPixels();
//        drawLine(window, CanvasPoint(0, 0), CanvasPoint(400, 300), Colour(white));
//        drawLine(window, CanvasPoint(800, 0), CanvasPoint(400, 300), Colour(white));
//        drawLine(window, CanvasPoint(400, 0), CanvasPoint(400, 600), Colour(white));
//        drawLine(window, CanvasPoint(266, 300), CanvasPoint(533, 300), Colour(white));
//        window.renderFrame();
//    }
//}
//void drawTriangle(DrawingWindow &window, const CanvasTriangle &triangle, const Colour &color) {
//    drawLine(window, triangle.vertices[0], triangle.vertices[1], color);
//    drawLine(window, triangle.vertices[1], triangle.vertices[2], color);
//    drawLine(window, triangle.vertices[0], triangle.vertices[2], color);
//}
////
//
//
//
//void sortVerticesByY(CanvasPoint &p1, CanvasPoint &p2, CanvasPoint &p3) {
//    if(p1.y > p2.y) std::swap(p1, p2);
//    if(p1.y > p3.y) std::swap(p1, p3);
//    if(p2.y > p3.y) std::swap(p2, p3);
//}
//
//int roundToInteger(float value) {
//    return static_cast<int>(value + 0.5);
//}
//
//void fillScanline(DrawingWindow &window, int y, float startX, float endX, const Colour &color) {
//    std::cout << "Scanning line at y = " << y << " from x = " << startX << " to x = " << endX
//              << " with color (" << color.red << ", " << color.green << ", " << color.blue << ")" << std::endl;
//
//    int xStart = static_cast<int>(startX);
//    int xEnd = static_cast<int>(endX);
//
//    uint32_t colorValue = (255 << 24) + (color.red << 16) + (color.green << 8) + color.blue;
//    for(int x = xStart; x <= xEnd; x++) {
//        window.setPixelColour(x, y, colorValue);
//    }
//}
//
//
//void drawFilledTriangle(DrawingWindow &window, const CanvasTriangle &triangle, const Colour &color) {
//    // Assuming you have a sortVerticesByY function from previous steps
//    CanvasPoint p1 = triangle.vertices[0];
//    CanvasPoint p2 = triangle.vertices[1];
//    CanvasPoint p3 = triangle.vertices[2];
//    sortVerticesByY(p1, p2, p3);
//
//    float slopeA = (p2.y - p1.y) ? (p2.x - p1.x) / (p2.y - p1.y) : 1;
//    float slopeB = (p3.y - p1.y) ? (p3.x - p1.x) / (p3.y - p1.y) : 1;
//
//    // Handle the bottom flat triangle
//    for(int y = roundToInteger(p1.y); y <= roundToInteger(p2.y); y++) {
//        float startX = p1.x + slopeA * (y - p1.y);
//        float endX = p1.x + slopeB * (y - p1.y);
//        fillScanline(window, y, startX, endX, color);
//    }
//
//    slopeA = (p3.y - p2.y) ? (p3.x - p2.x) / (p3.y - p2.y) : 1;
//
//    // Handle the top flat triangle
//    for(int y = roundToInteger(p2.y); y <= roundToInteger(p3.y); y++) {
//        float startX = p2.x + slopeA * (y - p2.y);
//        float endX = p1.x + slopeB * (y - p1.y);
//        fillScanline(window, y, startX, endX, color);
//    }
//    Colour white(255, 255, 255);
//    drawTriangle(window, triangle, white);
//}
//
//int main(int argc, char* argv[]) {
//    DrawingWindow window = DrawingWindow(800, 600, false);
//    bool running = true;
//
//    while (running) {
//        SDL_Event event;
//        while (window.pollForInputEvents(event)) {
//            if (event.type == SDL_KEYDOWN) {
//                if (event.key.keysym.sym == SDLK_u) {
//
//                    CanvasPoint p1(rand() % window.width, rand() % window.height);
//                    CanvasPoint p2(rand() % window.width, rand() % window.height);
//                    CanvasPoint p3(rand() % window.width, rand() % window.height);
//                    CanvasTriangle triangle(p1, p2, p3);
//
//                    Colour randomColor(rand() % 256, rand() % 256, rand() % 256);
//                    std::cout << "Generated color: " << randomColor.red << ", " << randomColor.green << ", " << randomColor.blue << std::endl;
//                    drawFilledTriangle(window, triangle, randomColor);
//                }
//            }
//            window.renderFrame();
//        }
//    }
//    return 0;
//}

