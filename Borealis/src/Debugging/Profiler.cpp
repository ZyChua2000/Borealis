#include <BorealisPCH.hpp>
#include <Debugging/Profiler.hpp>
#include <Tracy.hpp>
#include <common/TracySystem.hpp>
#include <cstring>  

//Tracy Profiler (https://github.com/wolfpld/tracy)

namespace Borealis
{
    // Method to record a custom plot value
    void TracyProfiler::recordPlot(const char* plotName, float value) {
        TracyPlot(plotName, value);  // Record a custom plot in Tracy
    }

    // Method to log a message in the profiler
    void TracyProfiler::logMessage(const char* message) {
        TracyMessage(message, strlen(message));  // Log a message in Tracy
    }

    // Method to log a colored message in the profiler
    void TracyProfiler::logMessageColored(const char* message, const vec4& color) {
        uint32_t packedColor = vec4ToColor(color);  // Convert vec4 to packed uint32_t color
        TracyMessageC(message, strlen(message), packedColor);  // Log a colored message in Tracy
    }

    // Methods for memory allocation tracking
    void TracyProfiler::trackAllocation(void* ptr, size_t size) {
        TracyAlloc(ptr, size);  // Track memory allocation in Tracy
    }

    void TracyProfiler::trackFree(void* ptr) {
        TracyFree(ptr);  // Track memory free in Tracy
    }

    void TracyProfiler::trackSecureAllocation(void* ptr, size_t size) {
        TracySecureAlloc(ptr, size);  // Track secure memory allocation in Tracy
    }

    void TracyProfiler::trackSecureFree(void* ptr) {
        TracySecureFree(ptr);  // Track secure memory free in Tracy
    }

    void TracyProfiler::sendAppInfo(const char* message) {
        TracyAppInfo(message, strlen(message));  // Send custom application info
    }

    // Mark the frame boundary, Help track overall performance at the frame level
    void TracyProfiler::markFrame(const char* frameName) {
        if (frameName) {
            FrameMarkNamed(frameName);  // Mark a frame with a custom name
        }
        else {
            FrameMark;  // Use the default frame marker
        }
    }

    //function marks the start of a frame with a specific name
    void TracyProfiler::markFrameStart(const char* frameName)
    {
        FrameMarkStart(frameName);
    }

    //function marks the end of a custom frame that was started using framemarkstart
    void TracyProfiler::markFrameEnd(const char* frameName)
    {
        FrameMarkEnd(frameName);
    }
    
    // Start a custom profiling zone, provides detailed insight into those frame
    void TracyProfiler::startZone(const char* name) {
        if (name) {
            static constexpr tracy::SourceLocationData __tracy_source_location61{ "name", __FUNCTION__, "C:\\Users\\cheng\\OneDrive\\Desktop\\Borealis\\Borealis\\src\\Debugging\\Profiler.cpp", (uint32_t)61, 0 }; tracy::ScopedZone ___tracy_scoped_zone(&__tracy_source_location61, true); // Start a named profiling zone
        }
        else {
            static constexpr tracy::SourceLocationData __tracy_source_location64{ nullptr, __FUNCTION__, "C:\\Users\\cheng\\OneDrive\\Desktop\\Borealis\\Borealis\\src\\Debugging\\Profiler.cpp", (uint32_t)64, 0 }; tracy::ScopedZone ___tracy_scoped_zone(&__tracy_source_location64, true); // Start an unnamed profiling zone
        }
    }
    
    // Destructor that ends the profiling zone
    TracyProfiler::~TracyProfiler() {
       
    }

    uint32_t TracyProfiler::vec4ToColor(const vec4& color) {
        uint8_t r = static_cast<uint8_t>(color.r * 255.0f);
        uint8_t g = static_cast<uint8_t>(color.g * 255.0f);
        uint8_t b = static_cast<uint8_t>(color.b * 255.0f);
        uint8_t a = static_cast<uint8_t>(color.a * 255.0f);

        // Pack color as 0xAARRGGBB
        return (a << 24) | (r << 16) | (g << 8) | b;
    }
}