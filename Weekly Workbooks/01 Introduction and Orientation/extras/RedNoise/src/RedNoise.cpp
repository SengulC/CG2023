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
#include <map>
#include "TextureMap.h"
#include "ModelTriangle.h"


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


////填图 fill the triangle
//void fillTriangle(DrawingWindow &window, const CanvasTriangle &triangle, const Colour &color) {
//    std::array<CanvasPoint, 3> sortedVertices = {triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]};
//    std::sort(sortedVertices.begin(), sortedVertices.end(), [](const CanvasPoint &a, const CanvasPoint &b) -> bool {
//        return a.y < b.y;
//    });
//
//    auto computeIntersection = [](const CanvasPoint &a, const CanvasPoint &b, float y) -> float {
//        if (a.y == b.y) return a.x;
//        return a.x + (b.x - a.x) * (y - a.y) / (b.y - a.y);
//    };
//
//    for (int y = static_cast<int>(sortedVertices[0].y); y < static_cast<int>(sortedVertices[1].y); y++) {
//        int startX = computeIntersection(sortedVertices[0], sortedVertices[2], y);
//        int endX = computeIntersection(sortedVertices[0], sortedVertices[1], y);
//        drawLine(window, CanvasPoint(startX, y), CanvasPoint(endX, y), color);
//    }
//
//    for (int y = static_cast<int>(sortedVertices[1].y); y <= static_cast<int>(sortedVertices[2].y); y++) {
//        int startX = computeIntersection(sortedVertices[0], sortedVertices[2], y);
//        int endX = computeIntersection(sortedVertices[1], sortedVertices[2], y);
//        drawLine(window, CanvasPoint(startX, y), CanvasPoint(endX, y), color);
//    }
//}

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


//void handleEvent(SDL_Event event, DrawingWindow &window) {
//    if (event.type == SDL_KEYDOWN) {
//        if (event.key.keysym.sym == SDLK_LEFT) std::cout << "LEFT" << std::endl;
//        else if (event.key.keysym.sym == SDLK_RIGHT) std::cout << "RIGHT" << std::endl;
//        else if (event.key.keysym.sym == SDLK_UP) std::cout << "UP" << std::endl;
//        else if (event.key.keysym.sym == SDLK_DOWN) std::cout << "DOWN" << std::endl;
//        else if (event.key.keysym.sym == SDLK_f) {
//            // Generate three random vertices
////            CanvasPoint p1(rand() % window.width, rand() % window.height);
////            CanvasPoint p2(rand() % window.width, rand() % window.height);
////            CanvasPoint p3(rand() % window.width, rand() % window.height);
//
//                CanvasPoint p1(160, 10);
//        p1.texturePoint = TexturePoint(195, 5);
//        CanvasPoint p2(300, 230);
//        p2.texturePoint = TexturePoint(395, 380);
//        CanvasPoint p3(10, 150);
//        p3.texturePoint = TexturePoint(65, 330);
//        // 创建三角形
//        CanvasTriangle triangle(p1, p2, p3);
//
//            // Generate a random color
//            Colour randomColor(rand() % 256, rand() % 256, rand() % 256);
//            fillTriangle(window, triangle, randomColor);
//            // Draw the triangle
//            Colour whiteColor(255, 255, 255);
//            drawTriangle(window, triangle, whiteColor);
//        }
//        else if (event.key.keysym.sym == SDLK_u) {
//            CanvasPoint p1(rand() % window.width, rand() % window.height);
//            CanvasPoint p2(rand() % window.width, rand() % window.height);
//            CanvasPoint p3(rand() % window.width, rand() % window.height);
//            CanvasTriangle triangle(p1, p2, p3);
//            Colour randomColor(rand() % 256, rand() % 256, rand() % 256);
//            drawTriangle(window, triangle, randomColor);
//        }
//    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
//        window.savePPM("output.ppm");
//        window.saveBMP("output.bmp");
//    }
//}




//int main() {
//    // 初始化窗口
//    DrawingWindow window(1200, 600, false);  // 假设您的窗口大小为800x600
//    // 加载纹理
//    TextureMap texture("/home/merlin/CG2023/Weekly Workbooks/03 Triangles and Textures/texture.ppm");
//    // 设置CanvasPoint和对应的TexturePoint
//    CanvasPoint p1(160, 10);
//    p1.texturePoint = TexturePoint(195, 5);
//    CanvasPoint p2(300, 230);
//    p2.texturePoint = TexturePoint(395, 380);
//    CanvasPoint p3(10, 150);
//    p3.texturePoint = TexturePoint(65, 330);
//    // 创建三角形
//    CanvasTriangle triangle(p1, p2, p3);
//    // 清空窗口 (假设黑色背景)
//    window.clearPixels();
//    // 填充三角形
//    fillTexturedTriangle(window, triangle, texture);
//
//
//
//    // 渲染
//    window.renderFrame();
//
//    // 事件循环，等待窗口关闭
//    bool running = true;
//    while (running) {
//        SDL_Event event;
//        while (window.pollForInputEvents(event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//            // 其他事件处理，如键盘、鼠标等
//            handleEvent(event, window);
//        }
//    }
//
//    return 0;
//}





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


std::vector<ModelTriangle> loadOBJ(const std::string &filename, const std::map<std::string, Colour>& palette) {
    std::vector<ModelTriangle> triangles;
    std::vector<glm::vec3> vertices;
    Colour currentColour;


    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return triangles;
    }

    std::string line;
    std::string currentMaterial; // Track the current material

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ' ');
        if (tokens.empty()) continue;

        if (tokens[0] == "v") {
            vertices.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
        } else if (tokens[0] == "usemtl") {
            currentMaterial = tokens[1];
            currentColour = palette.at(currentMaterial);  // Get the colour for the current material

        } else if (tokens[0] == "f") {
            std::array<glm::vec3, 3> faceVertices;

            for (int i = 0; i < 3; i++) {
                std::vector<std::string> faceTokens = split(tokens[i + 1], '/');
                faceVertices[i] = vertices[std::stoi(faceTokens[0]) - 1];
            }

            glm::vec3 normal = glm::normalize(glm::cross(faceVertices[1] - faceVertices[0], faceVertices[2] - faceVertices[0]));

            ModelTriangle triangle(faceVertices[0], faceVertices[1], faceVertices[2], palette.at(currentMaterial));
            triangle.normal = normal;
            triangles.push_back(triangle);
        }
    }

    file.close();
    return triangles;
}


CanvasPoint getCanvasIntersectionPoint(const glm::vec3& cameraPosition, const glm::vec3& vertexPosition, float focalLength, int screenWidth, int screenHeight) {
    glm::vec3 relativeVertex = vertexPosition - cameraPosition;

    // 这里使用了240作为缩放因子，如您所述
    float scaleFactor = 240.0f;

    float x = scaleFactor * (focalLength * (relativeVertex.x / relativeVertex.z)) + (screenWidth / 2);
    float y = scaleFactor * (focalLength * (relativeVertex.y / relativeVertex.z)) + (screenHeight / 2);
    std::cout << "Projected point: (" << x << ", " << y << ")" << std::endl;

    return CanvasPoint(x, y, relativeVertex.z);
}


//glm::vec3 cameraPosition(0.0f, 0.0f, 4.0f);  // Given camera position
//CanvasPoint projectedPoint = getCanvasIntersectionPoint(cameraPosition, vertexPosition, focalLength, imagePlaneWidth, imagePlaneHeight);
std::map<std::string, Colour> loadMTL(const std::string& filename) {
    std::map<std::string, Colour> palette;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the MTL file: " << filename << std::endl;
        return palette;
    }

    std::string currentMaterial;
    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 6) == "newmtl") {
            currentMaterial = line.substr(7);
        }
        else if (line.substr(0, 2) == "Kd" && !currentMaterial.empty()) {
            size_t pos1 = line.find(" ") + 1;
            size_t pos2 = line.find(" ", pos1) + 1;
            size_t pos3 = line.find(" ", pos2) + 1;

            float r = std::stof(line.substr(pos1, pos2 - pos1 - 1));
            float g = std::stof(line.substr(pos2, pos3 - pos2 - 1));
            float b = std::stof(line.substr(pos3));

            palette[currentMaterial] = Colour(r * 255, g * 255, b * 255);
        }
    }

    return palette;
}




float computeIntersection(const CanvasPoint &a, const CanvasPoint &b, float y) {
    if (a.y == b.y) return a.x; // 如果两点的y值相等，直接返回其中任意一个点的x值。
    return a.x + (b.x - a.x) * (y - a.y) / (b.y - a.y); // 线性插值公式
}

std::vector<std::vector<float>> depthBuffer(800, std::vector<float>(600, -std::numeric_limits<float>::infinity()));  // 假设800x600为窗口大小

void resetDepthBuffer() {
    for(auto &row : depthBuffer) {
        std::fill(row.begin(), row.end(), -std::numeric_limits<float>::infinity());
    }
}


void fillTriangle(DrawingWindow &window, const CanvasTriangle &triangle, const Colour &color) {
    std::array<CanvasPoint, 3> sortedVertices = {triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]};
    std::sort(sortedVertices.begin(), sortedVertices.end(), [](const CanvasPoint &a, const CanvasPoint &b) -> bool {
        return a.y < b.y;
    });

    // Interpolating the values based on another value
    auto interpolate = [](float from, float to, float t) -> float {
        return from + t * (to - from);
    };

    for (int y = static_cast<int>(sortedVertices[0].y); y <= static_cast<int>(sortedVertices[2].y); y++) {
        bool isUpper = y < sortedVertices[1].y;

        float depth1 = interpolate(sortedVertices[0].depth, isUpper ? sortedVertices[1].depth : sortedVertices[2].depth, (y - sortedVertices[0].y) / (isUpper ? sortedVertices[1].y - sortedVertices[0].y : sortedVertices[2].y - sortedVertices[0].y));
        float depth2 = interpolate(sortedVertices[0].depth, sortedVertices[2].depth, (y - sortedVertices[0].y) / (sortedVertices[2].y - sortedVertices[0].y));

        int startX = computeIntersection(sortedVertices[0], isUpper ? sortedVertices[1] : sortedVertices[2], y);
        int endX = computeIntersection(sortedVertices[0], sortedVertices[2], y);

        for (int x = startX; x <= endX; x++) {
            float depth = interpolate(depth1, depth2, (x - startX) / static_cast<float>(endX - startX));

            if(depth > depthBuffer[x][y]) {
                uint32_t packedColor = (color.red << 16) | (color.green << 8) | color.blue;
                window.setPixelColour(x, y, packedColor);
                depthBuffer[x][y] = depth;
            }
        }
    }
}



    int main() {
    const std::string filepath = "/home/merlin/CG2023/Weekly Workbooks/04 Wireframes and Rasterising/models/cornell-box.obj";
    std::vector<Colour> colourPalette;
    std::map<std::string, Colour> palette = loadMTL("/home/merlin/CG2023/Weekly Workbooks/04 Wireframes and Rasterising/models/cornell-box.mtl");
    std::vector<ModelTriangle> triangles = loadOBJ(filepath, palette);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    DrawingWindow window(800, 600, false);

    bool running = true;
    SDL_Event event;

    std::vector<ModelTriangle> model =loadOBJ(filepath, palette);
    glm::vec3 cameraPosition(0.0f, 0.0f, 8.0f);
    float focalLength = 2.0f;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        window.clearPixels(); // 清除像素缓冲区
        std::vector<CanvasTriangle> canvasTriangles;


        for (const ModelTriangle& modelTriangle : model) {
            CanvasPoint points[3];
            for (int i = 0; i < 3; i++) {
                const glm::vec3& vertex = modelTriangle.vertices[i];
                points[i] = getCanvasIntersectionPoint(cameraPosition, vertex, focalLength, 800, 600);
                window.setPixelColour(static_cast<int>(points[i].x), static_cast<int>(points[i].y), 0xFFFFFF); // 为顶点绘制白色点
            }
            CanvasTriangle canvasTriangle(points[0], points[1], points[2]);
            canvasTriangles.push_back(canvasTriangle);
        }

        for (auto it = canvasTriangles.begin(); it != canvasTriangles.end(); ++it) {
            size_t triangleIndex = std::distance(canvasTriangles.begin(), it);
            if (triangleIndex < model.size()) {
                const ModelTriangle& correspondingModelTriangle = model[triangleIndex];
//                drawTriangle(window, *it, Colour(255,255,255));

                const Colour& triangleColour = correspondingModelTriangle.colour;  // Use the triangle's colour directly
                fillTriangle(window, *it,triangleColour);
                resetDepthBuffer();
            } else {
                std::cerr << "Warning: Mismatch between canvasTriangles and model sizes." << std::endl;
            }
        }





        window.renderFrame(); // 这会将像素缓冲区推送到SDL_Texture并渲染它
    }

    // 由于您已使用DrawingWindow类，因此不再需要手动销毁SDL的资源
    SDL_Quit();
    return 0;
}










