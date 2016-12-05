# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
add_subdirectory (app)
add_subdirectory (library)