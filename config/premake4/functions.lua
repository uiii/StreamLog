function require_pkg_config()
    if os.execute("pkg-config --version &> /dev/null") ~= 0 then
        error("pkg-config is required")
    end
end

function require_pkg(pkg)
    if os.execute("pkg-config --exists " .. pkg) ~= 0 then
        error(pkg .. "is required")
    end

    buildoptions { "`pkg-config --cflags " .. pkg .. "`" }
    linkoptions { "`pkg-config --libs " .. pkg .. "`" }
end

function require_lib(lib)
    local path = os.findlib(lib)
    if path == nil then
        error(lib .. " is required")
    end
    print(path)
end
