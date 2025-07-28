# Lilica: Lua-Wrapped ImGui

Lilica is a lightweight C++ application that lets you define interactive graphical user interfaces using Lua scripting through the ImGui framework. It is ideal for tools, prototypes, or any GUI-based workflow where live scripting and flexibility are key.

---

[![image.png](https://i.postimg.cc/pL8JBjSM/image.png)](https://postimg.cc/gxzhzxdg)

## Features

- Create and modify GUI elements using Lua scripts
- Reload Lua scripts at runtime via a built-in debug interface
- Uses Dear ImGui with OpenGL and GLFW
- Modular C++ codebase

---

## Project Structure

```
lilica/
├── CMakeLists.txt
├── script.lua                  # Example Lua UI script
├── src/
│   ├── main.cpp                # Entry point
│   ├── gui_manager.{h,cpp}     # Window & rendering loop
│   ├── lua_helper.{h,cpp}      # Lua context and error handling
│   ├── imgui_binding.{h,cpp}   # Exposes ImGui to Lua
└── imgui/                      # Dear ImGui and backend sources
```

---

## Build Instructions

### Prerequisites

- CMake 3.20+
- A C++17 compiler
- Lua development files
- GLFW
- OpenGL

### Build (on Windows using vcpkg)

```
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

---

## Running the App

1. Ensure `script.lua` is available in the root directory.
2. Run the `lilica` binary.
3. The GUI defined in the Lua script will appear.
4. Use the built-in debug panel to reload or change scripts.

---

## Lua Scripting Example (`script.lua`)

```lua
function render_ui()
    imgui.Begin("Lua Window")

    imgui.Text("Hello from Lua!")

    if imgui.Button("Click Me") then
        print("You clicked the button!")
    end

    imgui.End()
end
```

---

## Debug Panel

The application includes a built-in debug window that allows:

- Viewing the currently loaded script
- Changing the script path
- Reloading scripts
- Viewing Lua error messages

---

## Available Lua ImGui Functions

The following functions are available from Lua and map directly to ImGui features:

### Basic Controls

- `imgui.Begin(name)` / `imgui.End()`  
  Creates a window. Call `End()` to close it.

- `imgui.Text(text)`  
  Displays static text.

- `imgui.Button(label)`  
  Returns `true` when clicked.

- `imgui.SameLine()`  
  Places next widget on the same horizontal line.

### Input Widgets

- `changed, new_value = imgui.Checkbox(label, current_value)`  
  Toggle a boolean value.

- `changed, new_value = imgui.SliderFloat(label, value, min, max)`  
  Float slider control.

- `changed, text = imgui.InputText(label, initial_text)`  
  Input box for strings.

- `changed, int_val = imgui.InputInt(label, initial_int)`  
  Input box for integers.

### Combo and List

- `changed, index = imgui.Combo(label, current_index, item_list)`  
  Dropdown menu.

- `changed, index = imgui.ListBox(label, current_index, item_list)`  
  Scrollable list box.

### Advanced Controls

- `changed, r, g, b = imgui.ColorEdit3(label, r, g, b)`  
  Color picker (RGB).

- `imgui.ProgressBar(fraction)`  
  Display a progress bar from 0.0 to 1.0.

- `open = imgui.TreeNode(label)`  
  Collapsible tree node. Use `imgui.TreePop()` to close.

- `imgui.BeginChild(id, width, height)` / `imgui.EndChild()`  
  Nested scrolling region or frame.

### Menus

- `open = imgui.BeginMenuBar()` / `imgui.EndMenuBar()`  
  Begin and end a menu bar (must be inside a window).

- `open = imgui.BeginMenu(label)` / `imgui.EndMenu()`  
  Dropdown menu.

- `selected = imgui.MenuItem(label)`  
  Menu item inside a menu.

---

## License

```
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do so, 
subject to the following conditions:

The above copyright notice and this permission notice shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT 
OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
```

---

## Credits

Lilica uses:
- Dear ImGui (https://github.com/ocornut/imgui)
- Lua
- GLFW
- OpenGL
