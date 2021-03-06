#include <future>
#include <iostream>
#include <random>
#include <string>
#include "../runtime/JavaClass.h"
#include "../runtime/JavaHeap.hpp"
#include "../runtime/MethodArea.h"
#include "NativeMethod.h"
#include "../vm/YVM.h"

JType* ydk_lang_IO_print_str(RuntimeEnv* env, JType** args, int numArgs) {
    JObject* str = (JObject*)args[0];
    if (nullptr != str) {
        auto fields = env->jheap->getFields(str);
        JArray* chararr = (JArray*)fields[0];
        auto lengthAndData = env->jheap->getElements(chararr);
        char* s = new char[lengthAndData.first + 1];
        for (int i = 0; i < lengthAndData.first; i++) {
            s[i] = (char)((JInt*)lengthAndData.second[i])->val;
        }
        s[lengthAndData.first] = '\0';
        std::cout << s;
        delete[] s;
    } else {
        std::cout << "null";
    }

    return nullptr;
}

JType* ydk_lang_IO_print_I(RuntimeEnv* env, JType** args, int numArgs) {
    JInt* num = (JInt*)args[0];
    std::cout << num->val;
    return nullptr;
}

JType* ydk_lang_IO_print_C(RuntimeEnv* env, JType** args, int numArgs) {
    JInt* num = (JInt*)args[0];
    std::cout << (char)num->val;
    return nullptr;
}

JType* java_lang_Math_random(RuntimeEnv* env, JType** args, int numArgs) {
    std::default_random_engine dre;
    std::uniform_int_distribution<int> realD;
    return new JDouble(realD(dre));
}

JType* java_lang_stringbuilder_append_I(RuntimeEnv* env, JType** args,
                                        int numArgs) {
    JObject* caller = (JObject*)args[0];
    JInt* numParameter = (JInt*)args[1];
    std::string str{};

    // append lhs string to str
    JArray* arr =
        dynamic_cast<JArray*>(env->jheap->getFieldByOffset(*caller, 0));
    if (arr != nullptr) {
        for (int i = 0; i < arr->length; i++) {
            str +=
                (char)dynamic_cast<JInt*>(env->jheap->getElement(*arr, i))->val;
        }
    }

    // convert Int to string and append on str
    str += std::to_string(numParameter->val);
    JArray* newArr = env->jheap->createCharArray(str, str.length());
    env->jheap->putFieldByOffset(*caller, 0, newArr);

    // remove old lhs string since new str overlapped it
    if (arr != nullptr) {
        env->jheap->removeArray(arr->offset);
    }

    return caller;
}

JType* java_lang_stringbuilder_append_C(RuntimeEnv* env, JType** args,
                                        int numArgs) {
    JObject* caller = (JObject*)args[0];
    JInt* numParameter = (JInt*)args[1];
    std::string str{};

    JArray* arr =
        dynamic_cast<JArray*>(env->jheap->getFieldByOffset(*caller, 0));
    if (arr != nullptr) {
        for (int i = 0; i < arr->length; i++) {
            str +=
                (char)dynamic_cast<JInt*>(env->jheap->getElement(*arr, i))->val;
        }
    }
    char c = numParameter->val;
    str += c;
    JArray* newArr = env->jheap->createCharArray(str, str.length());
    env->jheap->putFieldByOffset(*caller, 0, newArr);
    if (arr != nullptr) {
        env->jheap->removeArray(arr->offset);
    }
    return caller;
}

JType* java_lang_stringbuilder_append_str(RuntimeEnv* env, JType** args,
                                          int numArgs) {
    JObject* caller = (JObject*)args[0];
    JObject* strParameter = (JObject*)args[1];
    std::string str{};

    JArray* arr =
        dynamic_cast<JArray*>(env->jheap->getFieldByOffset(*caller, 0));
    if (nullptr != arr) {
        for (int i = 0; i < arr->length; i++) {
            str +=
                (char)dynamic_cast<JInt*>(env->jheap->getElement(*arr, i))->val;
        }
    }
    JArray* chararr =
        dynamic_cast<JArray*>(env->jheap->getFieldByOffset(*strParameter, 0));
    for (int i = 0; i < chararr->length; i++) {
        str +=
            (char)dynamic_cast<JInt*>(env->jheap->getElement(*chararr, i))->val;
    }

    JArray* newArr = env->jheap->createCharArray(str, str.length());
    env->jheap->putFieldByOffset(*caller, 0, newArr);

    if (arr != nullptr) {
        env->jheap->removeArray(arr->offset);
    }
    return caller;
}

JType* java_lang_stringbuilder_append_D(RuntimeEnv* env, JType** args,
                                        int numArgs) {
    JObject* caller = (JObject*)args[0];
    JDouble* numParameter = (JDouble*)args[1];
    std::string str{};

    JArray* arr =
        dynamic_cast<JArray*>(env->jheap->getFieldByOffset(*caller, 0));
    if (arr != nullptr) {
        for (int i = 0; i < arr->length; i++) {
            str +=
                (char)dynamic_cast<JInt*>(env->jheap->getElement(*arr, i))->val;
        }
    }
    str += std::to_string(numParameter->val);
    JArray* newArr = env->jheap->createCharArray(str, str.length());
    env->jheap->putFieldByOffset(*caller, 0, newArr);
    if (arr != nullptr) {
        env->jheap->removeArray(arr->offset);
    }
    return caller;
}

JType* java_lang_stringbuilder_tostring(RuntimeEnv* env, JType** args,
                                        int numArgs) {
    JObject* caller = (JObject*)args[0];
    JArray* value =
        dynamic_cast<JArray*>(env->jheap->getFieldByOffset(*caller, 0));
    char* carr = new char[value->length];
    for (int i = 0; i < value->length; i++) {
        carr[i] =
            (char)dynamic_cast<JInt*>(env->jheap->getElement(*value, i))->val;
    }
    JObject* str =
        env->jheap->createObject(*env->ma->findJavaClass("java/lang/String"));
    env->jheap->putFieldByOffset(
        *str, 0, env->jheap->createCharArray(carr, value->length));
    delete[] carr;

    return str;
}

JType* java_lang_thread_start(RuntimeEnv* env, JType** args, int numArgs) {
    auto* caller = (JObject*)args[0];
    auto* runnableTask = (JObject*)cloneValue(dynamic_cast<JObject*>(
        env->jheap->getFieldByName(yrt.ma->findJavaClass("java/lang/Thread"),
                                   "task", "Ljava/lang/Runnable;", caller)));

    YVM::executor.createThread();
    future<void> subThreadF = YVM::executor.submit([=]() {
#ifdef YVM_DEBUG_SHOW_THREAD_NAME
        std::cout << "[New Java Thread] ID:" << std::this_thread::get_id()
                  << "\n";
#endif
        const std::string& name = runnableTask->jc->getClassName();
        auto* jc = yrt.ma->loadClassIfAbsent(name);
        yrt.ma->linkClassIfAbsent(name);
        // For each execution thread, we have a code execution engine
        auto* frame = new JavaFrame;
        frame->pushFrame(1, 1);
        frame->top()->push(runnableTask);
        Interpreter exec{frame};

        yrt.ma->initClassIfAbsent(exec, name);
        // Push object reference and since Runnable.run() has no parameter, so
        // we dont need to push arguments since Runnable.run() has no parameter

        exec.invokeInterface(jc, "run", "()V");
    });
    YVM::executor.storeTaskFuture(subThreadF.share());

    return nullptr;
}
