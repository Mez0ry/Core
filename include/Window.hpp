#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <memory>
#include <functional>

#include <GLFW/glfw3.h>

struct WindowDeleter{
    void operator()(GLFWwindow* window){
        glfwDestroyWindow(window);
    }
};

class Window{
public:
    using ResizeCallbackType = std::function<void(int, int)>;
    using CloseCallbackType = std::function<void()>;
    using KeyCallbackType = std::function<void(int, int, int, int)>;
private:
    int m_Width, m_Height;
    std::shared_ptr<GLFWwindow> m_Window;
    ResizeCallbackType m_ResizeCallback;
    CloseCallbackType m_CloseCallback;
    KeyCallbackType m_KeyCallback;
public:
    Window(const char* title, uint16_t width, uint16_t height, GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);

    void SetWindowHint(int hint, int value);

    void SwapBuffers() const;

    int GetWidth() const;
    int GetHeight() const;
    std::shared_ptr<GLFWwindow> GetNativeWindow() const;

    void SetSelfAsContext() const;

    void SetResizeCallback(ResizeCallbackType callback);
    void SetCloseCallback(CloseCallbackType callback);
    void SetKeyCallback(KeyCallbackType callback);

    void Close();

    bool IsClosed() const;
public:
    operator GLFWwindow*() const{
        return m_Window.get();
    }
private:
    static void ResizeCallback(GLFWwindow* window, int width, int height);
    static void CloseCallback(GLFWwindow* window);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void SetupCallbacks();
};
#endif //!__WINDOW_HPP__