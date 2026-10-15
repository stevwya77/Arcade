#pragma once

#include <optional>
#include <string>
#include <string_view>

class SceneManager
{
private:
    friend class Engine;
    std::string currentScene_;
    std::optional<std::string> nextScene_;
    std::optional<std::string> FetchNextScene();

public:
    void ChangeScene(std::string_view name);
    void RestartCurrentScene();

};