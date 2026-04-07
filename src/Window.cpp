#include "Window.hpp"
#include "Base.hpp"

Window::Window(const char* title, uint16_t width, uint16_t height, GLFWmonitor *monitor, GLFWwindow *share) : m_Width(width), m_Height(height), m_Window(nullptr)
{
    m_Window = Ref<GLFWwindow>(glfwCreateWindow(width, height, title, monitor, share), WindowDeleter());
    if (!m_Window) {
        glfwTerminate();
    }

    glfwSetWindowUserPointer(m_Window.get(), this);

    SetupCallbacks();
}

void Window::SetWindowHint(int hint, int value)
{
    glfwWindowHint(hint, value);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(*this);
}

int Window::GetWidth() const { return m_Width; }

int Window::GetHeight() const
{
    return m_Height;
}

void Window::SetupCallbacks() {
    glfwSetWindowSizeCallback(m_Window.get(), ResizeCallback);
    glfwSetWindowCloseCallback(m_Window.get(), CloseCallback);
    glfwSetKeyCallback(m_Window.get(), KeyCallback);
}

std::shared_ptr<GLFWwindow> Window::GetNativeWindow() const
{
    return m_Window;
}

void Window::SetSelfAsContext() const {
    glfwMakeContextCurrent(*this);
}

void Window::SetResizeCallback(ResizeCallbackType callback)
{
    m_ResizeCallback = callback;
}

void Window::SetCloseCallback(CloseCallbackType callback) {
    m_CloseCallback = callback;
}

void Window::SetKeyCallback(KeyCallbackType callback) {
    m_KeyCallback = callback;
}

void Window::Close() {
    glfwSetWindowShouldClose((*this), GL_TRUE);
}

bool Window::IsClosed() const
{
    return glfwWindowShouldClose((*this));
}

void Window::ResizeCallback(GLFWwindow *window, int width, int height)
{
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self && self->m_ResizeCallback) {
        self->m_ResizeCallback(width, height);
    }
}

void Window::CloseCallback(GLFWwindow* window) {
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self && self->m_CloseCallback) {
        self->m_CloseCallback();
    }
}

void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self && self->m_KeyCallback) {
        self->m_KeyCallback(key, scancode, action, mods);
    }
}
