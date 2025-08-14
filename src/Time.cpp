#include "Time.h"

namespace Time {

double lastTime = glfwGetTime();
double currentTime = 0;
double deltaTime = 0;

void Update() {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
}

}
