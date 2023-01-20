#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/fetch.h>
#include <emscripten/html5.h>
#include <stdio.h>
#include <string.h>

// generate a function that create a pthread to print helloworld
void* print_hello(void* arg)
{
    // Fetch a url with emscripten fetch, with success and error callback
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_PERSIST_FILE;
    attr.onsuccess = [](emscripten_fetch_t* fetch) {
        printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
        // emscripten_fetch_close(fetch); // Free data associated with the fetch.
    };
    attr.onerror = [](emscripten_fetch_t* fetch) {
        printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
        // emscripten_fetch_close(fetch); // Also free data on failure.
    };
    // url of longserver
    // emscripten_fetch(&attr, "http://localhost:5118/sample/student");
    printf("Start to send request\n");
    // m_fetch = emscripten_fetch(&attr, "http://localhost:5118/sample/studentlong");
    emscripten_fetch(&attr, "http://localhost:5118/sample/studentlong");

    return NULL;
}

// Generate C++ class named Content which hold a struct of emscripten_fetch_t
class Context {
public:
    Context()
    {
    }

    void send_request_pthread()
    {
        pthread_t thread;
        int error = pthread_create(&thread, NULL, print_hello, NULL);
        if (error == 0) {
            m_thread = thread;
        } else {
            printf("Failed to create pthread");
        }
    }

    void cancel_request_pthread()
    {
        if (m_thread != 0) {
            pthread_cancel(m_thread);
            m_thread = 0;
        }
    }

    void send_request()
    {
        // Fetch a url with emscripten fetch, with success and error callback
        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);
        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_PERSIST_FILE;
        attr.onsuccess = [](emscripten_fetch_t* fetch) {
            printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
            // emscripten_fetch_close(fetch); // Free data associated with the fetch.
        };
        attr.onerror = [](emscripten_fetch_t* fetch) {
            printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
            // emscripten_fetch_close(fetch); // Also free data on failure.
        };
        // url of longserver
        // emscripten_fetch(&attr, "http://localhost:5118/sample/student");
        printf("Start to send request\n");
        m_fetch = emscripten_fetch(&attr, "http://localhost:5118/sample/studentlong");
    }

    ~Context()
    {
        if (m_fetch != NULL) {
            emscripten_fetch_close(m_fetch);
        }
    }

    emscripten_fetch_t* m_fetch;
    pthread_t m_thread;
};

// Send fetch request in a pthread
int main(void)
{
    // Embind C++ class to javascript
    // In JS
    // var c = new Module.Context();
    // c.send_request();
    emscripten::class_<Context>("Context")
        .constructor()
        .function("send_request", &Context::send_request)
        .function("send_request_pthread", &Context::send_request_pthread)
        .function("cancel_request_pthread", &Context::cancel_request_pthread);

    // printf("hello\n");
    return 0;
}