#include <CanvasTriangle.h>
#include <DrawingWindow.h>
#include <Utils.h>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>



#define WIDTH 320
#define HEIGHT 240


std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues) {
    float step = (to - from) / (numberOfValues - 1);
    std::vector<float> values(numberOfValues);
    for (int i = 0; i < numberOfValues; i++) {
        values[i] = from + step * i;
    }
    return values;
}

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

std::vector<glm::vec3> interpolateThreeElementValues(glm::vec3 from, glm::vec3 to, int numberOfValues) {
    std::vector<glm::vec3> interpolatedValues;
    if (numberOfValues <= 1) return interpolatedValues;  // Edge case
    glm::vec3 step = (to - from) / float(numberOfValues - 1);
    for (int i = 0; i < numberOfValues; i++) {
        interpolatedValues.push_back(from + step * float(i));
    }
    return interpolatedValues;
}
void draw(DrawingWindow &window) {
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
}


void handleEvent(SDL_Event event, DrawingWindow &window) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) std::cout << "LEFT" << std::endl;
		else if (event.key.keysym.sym == SDLK_RIGHT) std::cout << "RIGHT" << std::endl;
		else if (event.key.keysym.sym == SDLK_UP) std::cout << "UP" << std::endl;
		else if (event.key.keysym.sym == SDLK_DOWN) std::cout << "DOWN" << std::endl;
	} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		window.savePPM("output.ppm");
		window.saveBMP("output.bmp");
	}
}


int main(int argc, char *argv[]) {
    std::vector<float> result;
    result = interpolateSingleFloats(2.2, 8.5, 7);
    for(size_t i=0; i<result.size(); i++)
        std::cout << result[i] << " ";
    std::cout << std::endl;

    glm::vec3 from(1.0, 4.0, 9.2);
    glm::vec3 to(4.0, 1.0, 9.8);
    std::vector<glm::vec3> results = interpolateThreeElementValues(from, to, 4);
    for (glm::vec3 vec : results) {
        std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
    }


	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);
	SDL_Event event;
	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		draw(window);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
