-- script.lua
-- Global variables for UI state
slider_value = 0.5
button_clicked = false
checkbox_value = false
text_input = "Hello, Lua!"
combo_index = 0
list_index = 0
color = { 1.0, 0.0, 0.0 } -- RGB
int_value = 42
progress_value = 0.0
items = { "Option 1", "Option 2", "Option 3" }

-- Function to define the UI layout
function render_ui()
    -- Menu bar
    if imgui.BeginMenuBar() then
        if imgui.BeginMenu("File") then
            if imgui.MenuItem("New") then
                print("New selected")
            end
            if imgui.MenuItem("Quit") then
                print("Quit selected")
            end
            imgui.EndMenu()
        end
        imgui.EndMenuBar()
    end

    -- Main window
    imgui.Begin("Lua-Controlled ImGui Demo")

    -- Text
    imgui.Text("Welcome to the ImGui Demo!")

    -- Separator
    imgui.Separator()

    -- Button
    if imgui.Button("Toggle Button") then
        button_clicked = not button_clicked
    end
    imgui.SameLine()
    imgui.Text("Button State: " .. (button_clicked and "ON" or "OFF"))

    -- Checkbox
    local changed, new_value = imgui.Checkbox("Enable Feature", checkbox_value)
    if changed then
        checkbox_value = new_value
    end

    -- Slider
    local changed, new_value = imgui.SliderFloat("Volume", slider_value, 0.0, 1.0)
    if changed then
        slider_value = new_value
    end

    -- Input Text
    local changed, new_text = imgui.InputText("Name", text_input)
    if changed then
        text_input = new_text
    end

    -- Input Int
    local changed, new_int = imgui.InputInt("Count", int_value)
    if changed then
        int_value = new_int
    end

    -- Combo Box
    local changed, new_index = imgui.Combo("Select Option", combo_index, items)
    if changed then
        combo_index = new_index
    end

    -- List Box
    local changed, new_index = imgui.ListBox("Choose Item", list_index, items)
    if changed then
        list_index = new_index
    end

    -- Color Picker
    local changed, r, g, b = imgui.ColorEdit3("Pick Color", color[1], color[2], color[3])
    if changed then
        color = { r, g, b }
    end

    -- Progress Bar
    progress_value = progress_value + 0.01
    if progress_value > 1.0 then progress_value = 0.0 end
    imgui.ProgressBar(progress_value)

    -- Tree Node
    if imgui.TreeNode("Tree Example") then
        imgui.Text("This is inside a tree node")
        if imgui.Button("Tree Button") then
            print("Tree button clicked")
        end
        imgui.TreePop()
    end

    -- Child window
    imgui.BeginChild("ChildWindow", 0, 100)
    imgui.Text("This is a child window")
    if imgui.Button("Child Button") then
        print("Child button clicked")
    end
    imgui.EndChild()

    -- Display states
    imgui.Separator()
    imgui.Text("Slider Value: " .. slider_value)
    imgui.Text("Text Input: " .. text_input)
    imgui.Text("Int Value: " .. int_value)
    imgui.Text("Combo Selection: " .. items[combo_index + 1])
    imgui.Text("List Selection: " .. items[list_index + 1])
    imgui.Text(string.format("Color: R=%.2f, G=%.2f, B=%.2f", color[1], color[2], color[3]))
    imgui.Text("Progress: " .. string.format("%.2f", progress_value))

    imgui.End()
end