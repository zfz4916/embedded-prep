/*
这里用来写一个按键事件的回调大纲，纯中文描述
*/

#include <stdio.h>

//这里是按键事件的枚举类型
typedef enum {
    KEY_CLICK,
    KEY_DOUBLE_CLICK,
    KEY_TRIPLE_CLICK,
    KEY_LONG_CLICK,
    KEY_LONG_LONG_CLICK,
    KEY_EVENT_MAX
} KEY_EVENT;

void PlayPause(void) {
    printf("PlayPause\n");
}

void NextSong(void) {
    printf("NextSong\n");
}

void PrevSong(void) {
    printf("PrevSong\n");
}

void VolumeUp(void) {
    printf("VolumeUp\n");
}

void VolumeDown(void) {
    printf("VolumeDown\n");
}

// void CallBackKeyEvent(KEY_EVENT event) {
//     switch (event) {
//         case KEY_CLICK:
//             PlayPause();
//             break;
//         case KEY_DOUBLE_CLICK:
//             NextSong();
//             break;
//         case KEY_TROLE_CLICK:
//             PrevSong();
//             break;
//         case KEY_LONG_CLICK:
//             VolumeUp();
//             break;
//         case KEY_LONG_LONG_CLICK:
//             VolumeDown();
//             break;
//         default:
//             break;
//     }
// }



//函数指针类型 可以实现函数的回调
typedef void (*KeyCallback)(void);

//注册表 下标 = 事件类型，内容 = 该事件发生时该调谁。没注册的槽位是 NULL
static KeyCallback s_handlers[KEY_EVENT_MAX];

//注册函数 应用层启动时把自己的函数插进表里
void KeyRegister(KEY_EVENT event, KeyCallback fn) {
    if (event >= 0 && event < KEY_EVENT_MAX) {
        s_handlers[event] = fn;
    }
}

void CallBackKeyEvent(KEY_EVENT event) {
    if (event >= 0 && event < KEY_EVENT_MAX && s_handlers[event]) {
        s_handlers[event]();
    }
}

int main(void) {
    //应用层注册
    KeyRegister(KEY_CLICK,          PlayPause);
    KeyRegister(KEY_DOUBLE_CLICK,   NextSong);
    KeyRegister(KEY_TRIPLE_CLICK,   PrevSong);
    KeyRegister(KEY_LONG_CLICK,     VolumeUp);
    KeyRegister(KEY_LONG_LONG_CLICK, VolumeDown);

    CallBackKeyEvent(KEY_CLICK);
    CallBackKeyEvent(KEY_LONG_CLICK);

    KeyRegister(KEY_CLICK, NULL);       //注销后再触发 → 安全静默
    CallBackKeyEvent(KEY_CLICK);
    return 0;
}
