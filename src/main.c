#include <proto/exec.h>
#include <proto/intuition.h>
#define NO_INLINE_STDARG
#include <proto/muimaster.h>
#undef NO_INLINE_STDARG
#include <proto/utility.h>
#include <proto/icon.h>
#include <clib/alib_protos.h>
#include "g_misc.h"
#include <stdio.h>
#include <stdlib.h>

#include "pets/dog.h"
#include "pets/cat.h"
#include "pets/pets.h"

#define OPTION_USE_CLIB2 0

#if OPTION_USE_CLIB2
#include <stdlib_headers.h>
#endif

#define MUI_LIB_VERSION 19L

// We need to declare the libraries as "externally_visible" since we are using the option -fwhole-program in the Makefile
__attribute__((externally_visible)) struct ExecBase *SysBase;
__attribute__((externally_visible)) struct IntuitionBase *IntuitionBase = NULL;
__attribute__((externally_visible)) struct DosLibrary *DOSBase = NULL;
__attribute__((externally_visible)) struct UtilityBase *UtilityBase = NULL;
__attribute__((externally_visible)) struct GfxBase *GfxBase = NULL;
__attribute__((externally_visible)) struct Library *CxBase = NULL;
__attribute__((externally_visible)) struct Library *IconBase = NULL;
struct Library *MUIMasterBase = NULL;

#if OPTION_USE_CLIB2
// Declare all clib2 constructors and destructors
extern int __ctor_stdlib_memory_init(void);
extern int __ctor_stdlib_program_name_init(void);
extern int __ctor_stdio_init(void);
extern int __ctor_stdio_file_init(void);
extern int __ctor_math_init(void);
extern int __ctor_socket_init(void);
extern int __ctor_arg_init(void);
extern int __ctor_rexxvars_init(void);
extern int __ctor_dirent_init(void);
extern int __ctor_locale_init(void);
extern int __ctor_clock_init(void);
extern int __ctor_unistd_init(void);
extern int __ctor_timer_init(void);
extern int __ctor_usergroup_init(void);

extern int __dtor_usergroup_exit();
extern int __dtor_timer_exit();
extern int __dtor_unistd_exit();
extern int __dtor_locale_exit();
extern int __dtor_dirent_exit();
extern int __dtor_rexxvars_exit();
extern int __dtor_socket_exit();
extern int __dtor_math_exit();
extern int __dtor_workbench_exit();
extern int __dtor_stdio_exit();
extern int __dtor_stdlib_program_name_exit();
extern int __dtor_stdlib_memory_exit();
extern int __dtor___wildcard_expand_exit();
extern int __dtor_alloca_exit();
extern int __dtor___setenv_exit();
extern int __dtor___chdir_exit();
#endif

#if OPTION_USE_CLIB2
// Calls all constructors
static VOID fcntCallCtor(void)
{
    __ctor_stdlib_memory_init();
    __ctor_stdlib_program_name_init();
    __ctor_stdio_init();
    __ctor_stdio_file_init();
    __ctor_math_init();
    __ctor_socket_init();
    __ctor_arg_init();
    __ctor_rexxvars_init();
    __ctor_dirent_init();
    __ctor_locale_init();
    __ctor_clock_init();
    __ctor_unistd_init();
    __ctor_timer_init();
    __ctor_usergroup_init();
}

// Calls all destructors
static VOID fcntCallDtor(void)
{
    __dtor___wildcard_expand_exit();
    __dtor_alloca_exit();
    __dtor___setenv_exit();
    __dtor___chdir_exit();
    __dtor_usergroup_exit();
    __dtor_timer_exit();
    __dtor_unistd_exit();
    __dtor_locale_exit();
    __dtor_dirent_exit();
    __dtor_rexxvars_exit();
    __dtor_socket_exit();
    __dtor_math_exit();
    __dtor_workbench_exit();
    __dtor_stdio_exit();
    __dtor_stdlib_program_name_exit();
    __dtor_stdlib_memory_exit();
}
#endif

#define List(ftxt) ListviewObject, MUIA_Weight, 150, MUIA_Listview_Input, FALSE, MUIA_Listview_List, FloattextObject, MUIA_Frame, MUIV_Frame_ReadList, MUIA_Background, MUII_ReadListBack, MUIA_Floattext_Text, ftxt, MUIA_Floattext_TabSize, 4, MUIA_Floattext_Justify, TRUE, End, End
#define TxtInput(ftxt) StringObject, StringFrame, MUIA_String_Contents, ftxt, MUIA_String_MaxLen, 100, End
#define InvokeCreatePets 2

static APTR txt_dog_name, txt_dog_age, txt_dog_color;
static APTR txt_cat_name, txt_cat_age, txt_cat_color;
static APTR list, cm1, cm2;

extern void createPets(void);
// extern void createDog(Dog *dog, const char *name, int age, const char *color);

// This function is based on the MUI example "ShowHide" which can be downloaded from https://github.com/amiga-mui/muidev/releases/tag/MUI-3.9-2015R1
void MUIShowHide(void)
{
    Object *app, *window, *bt1, *bt2;

    // clang-format off
    app = ApplicationObject,
        MUIA_Application_Title, "Hello MUI",
        MUIA_Application_Version, "$VER: HelloMUI 1.0",
        MUIA_Application_Copyright, "(C) 2025 Matt Swart",
        MUIA_Application_Author, "Matt Swart",
        MUIA_Application_Description, "Hello MUI Test.",
        MUIA_Application_Base, "SHOWHIDE",

        SubWindow, window = WindowObject,
        MUIA_Window_Title, "Hello MUI",
        MUIA_Window_ID, MAKE_ID('S', 'H', 'H', 'D'),

            WindowContents, VGroup, GroupFrameT("Hello MUI"),

                Child, HGroup,                                                         
                        Child, VGroup,  GroupFrameT("Dog"),
                            Child, HSpace(200),
                            Child, HGroup,
                                Child, VGroup,
                                    Child, LLabel1("Name"),    
                                    Child, HSpace(50),
                                End,
                                Child, txt_dog_name = TxtInput("Dog1"),
                            End,
                            Child, HGroup,
                                Child, VGroup,
                                    Child, LLabel("Age"),
                                    Child, HSpace(50),
                                End,
                                Child, txt_dog_age = TxtInput("6"),
                            End,
                            Child, HGroup,
                                Child, VGroup,
                                    Child, LLabel("Color"),
                                    Child, HSpace(50),
                                End,
                                Child, txt_dog_color = TxtInput("Black"),
                            End,
                            Child, HGroup,
                                Child, LLabel("Create"),
                                Child, cm1 = CheckMark(TRUE),
                            End,                            
                        End,                    

                        Child, VGroup,  GroupFrameT("Cat"),
                            Child, HSpace(200),
                            Child, HGroup,
                                Child, VGroup,
                                    Child, LLabel1("Name"),    
                                    Child, HSpace(50),
                                End,
                                Child, txt_cat_name = TxtInput("Cat1"),
                            End,
                            Child, HGroup,
                                Child, VGroup,
                                    Child, LLabel("Age"),
                                    Child, HSpace(50),
                                End,
                                Child, txt_cat_age = TxtInput("3"),
                            End,
                            Child, HGroup,
                                Child, VGroup,
                                    Child, LLabel("Color"),
                                    Child, HSpace(50),
                                End,
                                Child, txt_cat_color = TxtInput("White"),
                            End,
                            Child, HGroup,
                                Child, LLabel("Create"),                                
                                Child, cm1 = CheckMark(TRUE),
                            End,  
                        End,                    
                End,    
                    
                Child, VGroup, GroupFrameT("Actions"),                    
                    Child, HGroup,
                        Child, bt1 = SimpleButton("Create Pet(s)"),
                        Child, bt2 = SimpleButton("Rub Pet(s)"),                        
                    End,
                    Child, list = List("Pet Feedback"),
                End,                                
            End,
        End,
    End;
    // clang-format on

    DoMethod(window, MUIM_Notify, MUIA_Window_CloseRequest, TRUE, app, 2, MUIM_Application_ReturnID, MUIV_Application_ReturnID_Quit);

    DoMethod(bt1, MUIM_Notify, MUIA_Pressed, FALSE, app, 2, MUIM_Application_ReturnID, InvokeCreatePets);
    // DoMethod(cm2, MUIM_Notify, MUIA_Selected, MUIV_EveryTime, bt2, 3, MUIM_Set, MUIA_ShowMe, MUIV_TriggerValue);

    /*
    ** This is the ideal input loop for an object oriented MUI application.
    ** Everything is encapsulated in classes, no return ids need to be used,
    ** we just check if the program shall terminate.
    ** Note that MUIM_Application_NewInput expects sigs to contain the result
    ** from Wait() (or 0). This makes the input loop significantly faster.
    */

    set(window, MUIA_Window_Open, TRUE);

    {
        ULONG sigs = 0;
        BOOL running = TRUE;
        LONG retid;

        while (running)
        {
            retid = (LONG)DoMethod(app, MUIM_Application_NewInput, &sigs);

            if (running && sigs)
            {
                sigs = Wait(sigs | SIGBREAKF_CTRL_C);
                if (sigs & SIGBREAKF_CTRL_C)
                    break;
            }

            switch (retid)
            {
            case MUIV_Application_ReturnID_Quit:
                running = FALSE;
                break;
            case InvokeCreatePets:
                createPets();
                break;
            default:
                break;
            }
        }
    }

    set(window, MUIA_Window_Open, FALSE);
}

// Does the clean up of all ressources
void cleanUP(void)
{
    if (IntuitionBase != NULL)
        CloseLibrary((struct Library *)IntuitionBase);

    if (DOSBase != NULL)
        CloseLibrary((struct Library *)DOSBase);

    if (UtilityBase != NULL)
        CloseLibrary((struct Library *)UtilityBase);

    if (GfxBase != NULL)
        CloseLibrary((struct Library *)GfxBase);

    if (CxBase != NULL)
        CloseLibrary(CxBase);

    if (IconBase != NULL)
        CloseLibrary(IconBase);

    if (MUIMasterBase != NULL)
        CloseLibrary(MUIMasterBase);
}

// We need to redefine some MUI functions because gcc, due to optimisations, is not always pushing all tags on the stack
Object *MUI_NewObject(CONST_STRPTR cl, Tag tags, ...)
{
    Object *ret = NULL;
    va_list param;
    struct TagItem *tagItem;

    va_start(param, tags);

    if ((tagItem = CopyTagsToMem(tags, param)))
    {
        ret = MUI_NewObjectA(cl, (struct TagItem *)tagItem);
        FreeTagMem(tagItem);
    }

    va_end(param);

    return (ret);
}

Object *MUI_MakeObject(LONG type, ...)
{
    Object *ret = NULL;
    va_list param;
    Tag firstTag;
    struct TagItem *tagItem;

    va_start(param, type);
    firstTag = (Tag)va_arg(param, Tag);

    if ((tagItem = CopyTagsToMem(firstTag, param)))
    {
        ret = MUI_MakeObjectA(type, (ULONG *)tagItem);
        FreeTagMem(tagItem);
    }

    va_end(param);

    return (ret);
}

LONG MUI_Request(APTR app, APTR win, ULONG flags, CONST_STRPTR title, CONST_STRPTR gadgets, CONST_STRPTR format, ...)
{
    LONG ret = 0L;

    va_list param;
    Tag firstTag;
    struct TagItem *tagItem;

    va_start(param, format);
    firstTag = (Tag)va_arg(param, Tag);

    if ((tagItem = CopyTagsToMem(firstTag, param)))
    {
        ret = MUI_RequestA(app, win, flags, title, gadgets, format, tagItem);
        FreeTagMem(tagItem);
    }

    va_end(param);

    return (ret);
}

APTR MUI_AllocAslRequestTags(unsigned long reqType, Tag Tag1, ...)
{
    APTR ret = NULL;
    va_list param;
    struct TagItem *tagItem;

    va_start(param, Tag1);

    if ((tagItem = CopyTagsToMem(Tag1, param)))
    {
        ret = MUI_AllocAslRequest(reqType, (struct TagItem *)tagItem);
        FreeTagMem(tagItem);
    }

    va_end(param);

    return (ret);
}

BOOL MUI_AslRequestTags(APTR requester, Tag Tag1, ...)
{
    BOOL ret = FALSE;
    va_list param;
    struct TagItem *tagItem;

    va_start(param, Tag1);

    if ((tagItem = CopyTagsToMem(Tag1, param)))
    {
        ret = MUI_AslRequest(requester, (struct TagItem *)tagItem);
        FreeTagMem(tagItem);
    }

    va_end(param);

    return (ret);
}

void createPets(void)
{
    LONG isChecked = 0;
    get(cm1, MUIA_Selected, &isChecked);

    if (isChecked)
    {
        char *dogName;
        char *dogAge;
        char *dogColor;
        get(txt_dog_name, MUIA_String_Contents, &dogName);
        get(txt_dog_age, MUIA_String_Contents, &dogAge);
        get(txt_dog_color, MUIA_String_Contents, &dogColor);

        Dog *dog = (Dog *)malloc(sizeof(Dog));
        if (dog)
        {
            createDog(dog, dogName, atoi(dogAge), dogColor);
            // char response[100];
            // dog->funcRefTable->patAnimal(dog, &response);
            // DoMethod(list, MUIM_List_InsertSingle, response, MUIV_List_Insert_Bottom);
        }
    }

    isChecked = 0;
    get(cm2, MUIA_Selected, &isChecked);

    if (isChecked)
    {
        char *catName;
        char *catAge;
        char *catColor;
        get(txt_cat_age, MUIA_String_Contents, &catAge);
        get(txt_cat_color, MUIA_String_Contents, &catColor);
        get(txt_cat_name, MUIA_String_Contents, &catName);

        Cat *cat = (Cat *)malloc(sizeof(Cat));
        if (cat)
        {
            createCat(cat, catName, atoi(catAge), catColor);
            // char response[100];
            // cat->funcRefTable->patAnimal(cat, &response);
            // DoMethod(list, MUIM_List_InsertSingle, response, MUIV_List_Insert_Bottom);
        }
    }
}

// Entry of our code
int main(int argc, char **argv)
{
    SysBase = *((struct ExecBase **)4UL);
    struct Process *proc;
    struct WBStartup *wbmsg = NULL;

    // We check if our program has been started by the workbench or by the shell
    proc = (struct Process *)FindTask(NULL);

    if (proc->pr_CLI == NULL)
    {
        // We have been launched by workbench: we wait for the startup message
        WaitPort(&proc->pr_MsgPort);
        wbmsg = (struct WBStartup *)GetMsg(&proc->pr_MsgPort);
    }

#if OPTION_USE_CLIB2
    __WBenchMsg = wbmsg;    // this variable is used in __ctor_arg_init()
    __exit_blocked = FALSE; // this will push exit() and similar functions to longjmp to target set by setjmp()
#endif

    // We open the libraries (required since we are linking with alib; please see https://github.com/jyoberle/alib for details)
    IntuitionBase = (struct IntuitionBase *)OpenLibrary((CONST_STRPTR) "intuition.library", 0L);
    DOSBase = (struct DosLibrary *)OpenLibrary((CONST_STRPTR) "dos.library", 0L);
    UtilityBase = (struct UtilityBase *)OpenLibrary((CONST_STRPTR) "utility.library", 0L);
    GfxBase = (struct GfxBase *)OpenLibrary("graphics.library", 0);
    CxBase = OpenLibrary("commodities.library", 0);
    IconBase = OpenLibrary("icon.library", 0);
    MUIMasterBase = OpenLibrary("muimaster.library", MUI_LIB_VERSION);

    if (IntuitionBase && DOSBase && UtilityBase && GfxBase && CxBase && IconBase && MUIMasterBase)
    {
#if OPTION_USE_CLIB2
        __UtilityBase = UtilityBase; // we need to add this because of macro DECLARE_UTILITYBASE()

        if (setjmp(__exit_jmp_buf) != 0)
            goto out; // target for exit

        fcntCallCtor(); // call the constructors
#endif

        // If all libs are available, we open the MUI window
        MUIShowHide();

#if OPTION_USE_CLIB2
        printf("This is an example of use of clib2\n");

    out:
        fcntCallDtor(); // call the destructors
#endif
    }

    // Before leaving, we close all libraries
    cleanUP();

    if (wbmsg != NULL)
    {
        // If needed, we reply to the workbench message
        Forbid();
        ReplyMsg((struct Message *)wbmsg);
    }
}

__attribute__((used)) __attribute__((section(".text.unlikely"))) void _start(int argc, char **argv)
{
    main(argc, argv);
}