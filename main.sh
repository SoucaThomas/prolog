# Build the project
cmake -S . -B build && cmake --build build

# Check if build was successful
if [ $? -eq 0 ]; then
    # Run the executable
    ./build/prolog_interpreter
else
    echo "Build failed!"
    exit 1
fi

