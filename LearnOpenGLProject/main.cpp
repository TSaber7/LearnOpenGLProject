#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{    
    //ʵ����GLFW����
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //����һ�����ڶ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    //��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //�����ӿ�
    glViewport(0, 0, 800, 600);

    //ע��ص����������ڴ�С�仯ʱ����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //��д������ɫ��Դ��
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    //����������ɫ������
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //������ɫ��
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //ƬԪ��ɫ��ͬ��
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //����Ϊ��ɫ���������
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //���õ�ǰ��ɫ������
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //���嶥������
    //float vertices[] = {
    //0.5f, 0.5f, 0.0f,   // ���Ͻ�
    //0.5f, -0.5f, 0.0f,  // ���½�
    //-0.5f, -0.5f, 0.0f, // ���½�
    //-0.5f, 0.5f, 0.0f   // ���Ͻ�
    //};

    //��ʹ�������ľ��ζ�������
    float vertices[] = {
    0.5f, 0.5f, 0.0f,   // ���Ͻ�
    0.5f, -0.5f, 0.0f,  // ���½�
    -0.5f, -0.5f, 0.0f, // ���½�
    -0.5f, -0.5f, 0.0f, // ���½�
    -0.5f, 0.5f, 0.0f,   // ���Ͻ�
    0.5f, 0.5f, 0.0f,   // ���Ͻ�
    };

    //������������
    unsigned int indices[] = { // ע��������0��ʼ! 
        0, 1, 3, // ��һ��������
        1, 2, 3  // �ڶ���������
    };

    //����VBO��VAO��EBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    //��VAO���м�¼
    glBindVertexArray(VAO);

    //��VBO��EBO�����ƶ������ݵ�VBO,�������ݵ�EBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //���Ӷ������Ե����ò��������ԣ��⽫����¼��VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //��¼��ɣ��Ƚ��VAO����ΪVAO���¼EBO�İ���Ϣ
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    

    //��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        //��������
        processInput(window);
        
        //��Ⱦָ��
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
        //��VAO������Ⱦ
        glBindVertexArray(VAO);

        //�߿�ģʽ
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //ֻʹ�ö������ݻ���
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //ʹ����������
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //��Ⱦ��ɺ���
        glBindVertexArray(0);

        //��ѯ�¼�
        glfwPollEvents();
        //˫���彻��
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}