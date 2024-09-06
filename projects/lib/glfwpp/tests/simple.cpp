#include <glad/glad.h>
#include <glfw/glfw.hpp>

#include <toml++/toml.hpp>

#include <iostream>
#include <sstream>
#include <string_view>

#include <set>
#include <bitset>
#include <unordered_map>
#include <functional>

#include <algorithm>
#include <numeric>
#include <random>

#include <cassert>
#include <cstdlib>

using namespace std::string_literals;

struct glLoadContext
{
  public: // types

    using Func_glAnyProc = void();

    template<typename... Args>
    using Func_glProc = void(Args...);

    template<typename... Args>
    class glFunctor
    {
      public:

        using glProcType = Func_glProc<Args...>;
        const std::string func_name;

      public:

        inline glFunctor(std::string_view func_name, std::function<Func_glAnyProc *(std::string_view)> gl_load_proc)
            : func_name(func_name)
            , proc_(reinterpret_cast<glProcType *>(gl_load_proc(func_name)))
        {
        }

        inline bool
        empty() const
        {
            return proc_ == nullptr;
        }

        inline void
        operator()(Args... args) const
        {
            if (proc_)
            {
                proc_(args...);
            }
            else
            {
                std::string error_msg {"OpenGL function " + func_name + " not loaded from context"};
                std::cerr << error_msg << std::endl;
                throw std::runtime_error(error_msg);
            }
        }

      private:

        Func_glProc<Args...> *proc_ = nullptr;
    };

    // OpenGl 4.6 core functors
    // clang-format off
    using Functor_glActiveShaderProgram                         = glFunctor<GLuint, GLuint>;
    using Functor_glActiveTexture                               = glFunctor<GLenum>;
    using Functor_glAttachShader                                = glFunctor<GLuint, GLuint>;
    using Functor_glBeginConditionalRender                      = glFunctor<GLuint, GLenum>;
    using Functor_glBeginQuery                                  = glFunctor<GLuint, const GLsizei, GLchar * const *, GLenum>;
    using Functor_glBeginQueryIndexed                           = glFunctor<GLenum, GLuint, GLuint>;
    using Functor_glBeginTransformFeedback                      = glFunctor<GLenum>;
    using Functor_glBindAttribLocation                          = glFunctor<GLuint, GLuint, const GLchar *>;
    using Functor_glBindBuffer                                  = glFunctor<GLenum, GLuint>;
    using Functor_glBindBufferBase                              = glFunctor<GLenum, GLuint, GLuint>;
    using Functor_glBindBufferRange                             = glFunctor<GLenum, GLuint, GLuint, GLintptr, GLsizeiptr>;
    using Functor_glBindBuffersBase                             = glFunctor<GLenum, GLuint, GLsizei, const GLuint *>;
    using Functor_glBindBuffersRange                            = glFunctor<GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *>;
    using Functor_glBindFragDataLocation                        = glFunctor<GLuint, GLuint, const GLchar *>;
    using Functor_glBindFragDataLocationIndexed                 = glFunctor<GLuint, GLuint, GLuint, const GLchar *>;
    using Functor_glBindFramebuffer                             = glFunctor<GLenum, GLuint>;
    using Functor_glBindImageTexture                            = glFunctor<GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum>;
    using Functor_glBindImageTextures                           = glFunctor<GLuint, GLsizei, const GLuint *>;
    using Functor_glBindProgramPipeline                         = glFunctor<GLuint>;
    using Functor_glBindRenderbuffer                            = glFunctor<GLenum, GLuint>;
    using Functor_glBindSampler                                 = glFunctor<GLuint, GLuint>;
    using Functor_glBindSamplers                                = glFunctor<GLuint, GLsizei, const GLuint *>;
    using Functor_glBindTexture                                 = glFunctor<GLenum, GLuint>;
    using Functor_glBindTextures                                = glFunctor<GLuint, GLsizei, const GLuint *>;
    using Functor_glBindTransformFeedback                       = glFunctor<GLenum, GLuint>;
    using Functor_glBindVertexArray                             = glFunctor<GLuint>;
    using Functor_glBindVertexBuffer                            = glFunctor<GLuint, GLuint, GLintptr, GLsizei>;
    using Functor_glBlendColor                                  = glFunctor<GLfloat, GLfloat, GLfloat, GLfloat>;
    using Functor_glBlendEquation                               = glFunctor<GLenum>;
    using Functor_glBlendEquationSeparate                       = glFunctor<>; // TODO: add function args
    using Functor_glBlendFunc                                   = glFunctor<>; // TODO: add function args
    using Functor_glBlendFuncSeparate                           = glFunctor<>; // TODO: add function args
    using Functor_glBlendFuncSeparatei                          = glFunctor<>; // TODO: add function args
    using Functor_glBlitFramebuffer                             = glFunctor<>; // TODO: add function args
    using Functor_glBufferData                                  = glFunctor<>; // TODO: add function args
    using Functor_glBufferStorage                               = glFunctor<>; // TODO: add function args
    using Functor_glBufferSubData                               = glFunctor<>; // TODO: add function args
    using Functor_glCheckFramebufferStatus                      = glFunctor<>; // TODO: add function args
    using Functor_glClampColor                                  = glFunctor<>; // TODO: add function args
    using Functor_glClear                                       = glFunctor<GLbitfield>;
    using Functor_glClearBuffer                                 = glFunctor<>; // TODO: add function args
    using Functor_glClearBufferData                             = glFunctor<>; // TODO: add function args
    using Functor_glClearBufferSubData                          = glFunctor<>; // TODO: add function args
    using Functor_glClearColor                                  = glFunctor<GLfloat, GLfloat, GLfloat, GLfloat>;
    using Functor_glClearDepth                                  = glFunctor<>; // TODO: add function args
    using Functor_glClearStencil                                = glFunctor<>; // TODO: add function args
    using Functor_glClearTexImage                               = glFunctor<>; // TODO: add function args
    using Functor_glClearTexSubImage                            = glFunctor<>; // TODO: add function args
    using Functor_glClientWaitSync                              = glFunctor<>; // TODO: add function args
    using Functor_glColorMask                                   = glFunctor<>; // TODO: add function args
    using Functor_glCompileShader                               = glFunctor<>; // TODO: add function args
    using Functor_glCompressedTexImage1D                        = glFunctor<>; // TODO: add function args
    using Functor_glCompressedTexImage2D                        = glFunctor<>; // TODO: add function args
    using Functor_glCompressedTexImage3D                        = glFunctor<>; // TODO: add function args
    using Functor_glCompressedTexSubImage1D                     = glFunctor<>; // TODO: add function args
    using Functor_glCompressedTexSubImage2D                     = glFunctor<>; // TODO: add function args
    using Functor_glCompressedTexSubImage3D                     = glFunctor<>; // TODO: add function args
    using Functor_glCopyBufferSubData                           = glFunctor<>; // TODO: add function args
    using Functor_glCopyImageSubData                            = glFunctor<>; // TODO: add function args
    using Functor_glCopyTexImage1D                              = glFunctor<>; // TODO: add function args
    using Functor_glCopyTexImage2D                              = glFunctor<>; // TODO: add function args
    using Functor_glCopyTexSubImage1D                           = glFunctor<>; // TODO: add function args
    using Functor_glCopyTexSubImage2D                           = glFunctor<>; // TODO: add function args
    using Functor_glCopyTexSubImage3D                           = glFunctor<>; // TODO: add function args
    using Functor_glBindVertexBuffers                           = glFunctor<>; // TODO: add function args
    using Functor_glCreateProgram                               = glFunctor<>; // TODO: add function args
    using Functor_glCreateShader                                = glFunctor<>; // TODO: add function args
    using Functor_glCreateShaderProgram                         = glFunctor<>; // TODO: add function args
    using Functor_glCreateShaderProgramv                        = glFunctor<>; // TODO: add function args
    using Functor_glCullFace                                    = glFunctor<>; // TODO: add function args
    using Functor_glDebugMessageCallback                        = glFunctor<>; // TODO: add function args
    using Functor_glDebugMessageControl                         = glFunctor<>; // TODO: add function args
    using Functor_glDebugMessageInsert                          = glFunctor<>; // TODO: add function args
    using Functor_glDeleteBuffers                               = glFunctor<>; // TODO: add function args
    using Functor_glDeleteFramebuffers                          = glFunctor<>; // TODO: add function args
    using Functor_glDeleteProgram                               = glFunctor<>; // TODO: add function args
    using Functor_glDeleteProgramPipelines                      = glFunctor<>; // TODO: add function args
    using Functor_glDeleteQueries                               = glFunctor<>; // TODO: add function args
    using Functor_glDeleteRenderbuffers                         = glFunctor<>; // TODO: add function args
    using Functor_glDeleteSamplers                              = glFunctor<>; // TODO: add function args
    using Functor_glDeleteShader                                = glFunctor<>; // TODO: add function args
    using Functor_glDeleteSync                                  = glFunctor<>; // TODO: add function args
    using Functor_glDeleteTextures                              = glFunctor<>; // TODO: add function args
    using Functor_glDeleteTransformFeedbacks                    = glFunctor<>; // TODO: add function args
    using Functor_glDeleteVertexArrays                          = glFunctor<>; // TODO: add function args
    using Functor_glDepthFunc                                   = glFunctor<>; // TODO: add function args
    using Functor_glDepthMask                                   = glFunctor<>; // TODO: add function args
    using Functor_glDepthRange                                  = glFunctor<>; // TODO: add function args
    using Functor_glDepthRangeArray                             = glFunctor<>; // TODO: add function args
    using Functor_glDepthRangeIndexed                           = glFunctor<>; // TODO: add function args
    using Functor_glDetachShader                                = glFunctor<>; // TODO: add function args
    using Functor_glDisable                                     = glFunctor<>; // TODO: add function args
    using Functor_glDisablei                                    = glFunctor<>; // TODO: add function args
    using Functor_glDisableVertexAttribArray                    = glFunctor<>; // TODO: add function args
    using Functor_glDispatchCompute                             = glFunctor<>; // TODO: add function args
    using Functor_glDispatchComputeIndirect                     = glFunctor<>; // TODO: add function args
    using Functor_glDrawArrays                                  = glFunctor<>; // TODO: add function args
    using Functor_glDrawArraysIndirect                          = glFunctor<>; // TODO: add function args
    using Functor_glDrawArraysInstanced                         = glFunctor<>; // TODO: add function args
    using Functor_glDrawArraysInstancedBaseInstance             = glFunctor<>; // TODO: add function args
    using Functor_glDrawBuffer                                  = glFunctor<>; // TODO: add function args
    using Functor_glDrawBuffers                                 = glFunctor<>; // TODO: add function args
    using Functor_glDrawElements                                = glFunctor<>; // TODO: add function args
    using Functor_glDrawElementsBaseVertex                      = glFunctor<>; // TODO: add function args
    using Functor_glDrawElementsIndirect                        = glFunctor<>; // TODO: add function args
    using Functor_glDrawElementsInstanced                       = glFunctor<>; // TODO: add function args
    using Functor_glDrawElementsInstancedBaseInstance           = glFunctor<>; // TODO: add function args
    using Functor_glDrawElementsInstancedBaseVertex             = glFunctor<>; // TODO: add function args
    using Functor_glDrawElementsInstancedBaseVertexBaseInstance = glFunctor<>; // TODO: add function args
    using Functor_glDrawRangeElements                           = glFunctor<>; // TODO: add function args
    using Functor_glDrawRangeElementsBaseVertex                 = glFunctor<>; // TODO: add function args
    using Functor_glDrawTransformFeedback                       = glFunctor<>; // TODO: add function args
    using Functor_glDrawTransformFeedbackInstanced              = glFunctor<>; // TODO: add function args
    using Functor_glDrawTransformFeedbackStream                 = glFunctor<>; // TODO: add function args
    using Functor_glDrawTransformFeedbackStreamInstanced        = glFunctor<>; // TODO: add function args
    using Functor_glEnable                                      = glFunctor<>; // TODO: add function args
    using Functor_glEnablei                                     = glFunctor<>; // TODO: add function args
    using Functor_glEnableVertexAttribArray                     = glFunctor<>; // TODO: add function args
    using Functor_glEndConditionalRender                        = glFunctor<>; // TODO: add function args
    using Functor_glEndQuery                                    = glFunctor<>; // TODO: add function args
    using Functor_glEndQueryIndexed                             = glFunctor<>; // TODO: add function args
    using Functor_glEndTransformFeedback                        = glFunctor<>; // TODO: add function args
    using Functor_glFenceSync                                   = glFunctor<>; // TODO: add function args
    using Functor_glFinish                                      = glFunctor<>; // TODO: add function args
    using Functor_glFlush                                       = glFunctor<>; // TODO: add function args
    using Functor_glFlushMappedBufferRange                      = glFunctor<>; // TODO: add function args
    using Functor_glFramebufferParameter                        = glFunctor<>; // TODO: add function args
    using Functor_glFramebufferParameteri                       = glFunctor<>; // TODO: add function args
    using Functor_glFramebufferRenderbuffer                     = glFunctor<>; // TODO: add function args
    using Functor_glFramebufferTexture                          = glFunctor<>; // TODO: add function args
    using Functor_glFramebufferTexture1D                        = glFunctor<>; // TODO: add function args
    using Functor_glFramebufferTexture2D                        = glFunctor<>; // TODO: add function args
    using Functor_glFramebufferTexture3D                        = glFunctor<>; // TODO: add function args
    using Functor_glFramebufferTextureLayer                     = glFunctor<>; // TODO: add function args
    using Functor_glFrontFace                                   = glFunctor<>; // TODO: add function args
    using Functor_glGenBuffers                                  = glFunctor<>; // TODO: add function args
    using Functor_glGenerateMipmap                              = glFunctor<>; // TODO: add function args
    using Functor_glGenFramebuffers                             = glFunctor<>; // TODO: add function args
    using Functor_glGenProgramPipelines                         = glFunctor<>; // TODO: add function args
    using Functor_glGenQueries                                  = glFunctor<>; // TODO: add function args
    using Functor_glGenRenderbuffers                            = glFunctor<>; // TODO: add function args
    using Functor_glGenSamplers                                 = glFunctor<>; // TODO: add function args
    using Functor_glGenTextures                                 = glFunctor<>; // TODO: add function args
    using Functor_glGenTransformFeedbacks                       = glFunctor<>; // TODO: add function args
    using Functor_glGenVertexArrays                             = glFunctor<>; // TODO: add function args
    using Functor_glGet                                         = glFunctor<>; // TODO: add function args
    using Functor_glGetBooleanv                                 = glFunctor<>; // TODO: add function args
    using Functor_glGetDoublev                                  = glFunctor<>; // TODO: add function args
    using Functor_glGetFloatv                                   = glFunctor<>; // TODO: add function args
    using Functor_glGetInteger64v                               = glFunctor<>; // TODO: add function args
    using Functor_glGetIntegerv                                 = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveAtomicCounterBuffer                = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveAtomicCounterBufferiv              = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveAttrib                             = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveSubroutineName                     = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveSubroutineUniform                  = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveSubroutineUniformName              = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveUniform                            = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveUniformBlock                       = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveUniformBlockName                   = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveUniformName                        = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveUniforms                           = glFunctor<>; // TODO: add function args
    using Functor_glGetActiveUniformsiv                         = glFunctor<>; // TODO: add function args
    using Functor_glGetAttachedShaders                          = glFunctor<>; // TODO: add function args
    using Functor_glGetAttribLocation                           = glFunctor<>; // TODO: add function args
    using Functor_glGetBufferParameter                          = glFunctor<>; // TODO: add function args
    using Functor_glGetBufferPointer                            = glFunctor<>; // TODO: add function args
    using Functor_glGetBufferSubData                            = glFunctor<>; // TODO: add function args
    using Functor_glGetCompressedTexImage                       = glFunctor<>; // TODO: add function args
    using Functor_glGetDebugMessageLog                          = glFunctor<>; // TODO: add function args
    using Functor_glGetError                                    = glFunctor<>; // TODO: add function args
    using Functor_glGetFragDataIndex                            = glFunctor<>; // TODO: add function args
    using Functor_glGetFragDataLocation                         = glFunctor<>; // TODO: add function args
    using Functor_glGetFramebufferAttachmentParameter           = glFunctor<>; // TODO: add function args
    using Functor_glGetFramebufferParameter                     = glFunctor<>; // TODO: add function args
    using Functor_glGetFramebufferParameteriv                   = glFunctor<>; // TODO: add function args
    using Functor_glGetInternalformat                           = glFunctor<>; // TODO: add function args
    using Functor_glGetMultisample                              = glFunctor<>; // TODO: add function args
    using Functor_glGetObjectLabel                              = glFunctor<>; // TODO: add function args
    using Functor_glGetObjectPtrLabel                           = glFunctor<>; // TODO: add function args
    using Functor_glGetProgram                                  = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramBinary                            = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramInfoLog                           = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramInterface                         = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramPipeline                          = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramPipelineInfoLog                   = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramResource                          = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramResourceLocation                  = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramResourceLocationIndex             = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramResourceIndex                     = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramResourceName                      = glFunctor<>; // TODO: add function args
    using Functor_glGetProgramStage                             = glFunctor<>; // TODO: add function args
    using Functor_glGetQuery                                    = glFunctor<>; // TODO: add function args
    using Functor_glGetQueryIndexed                             = glFunctor<>; // TODO: add function args
    using Functor_glGetQueryObject                              = glFunctor<>; // TODO: add function args
    using Functor_glGetRenderbufferParameter                    = glFunctor<>; // TODO: add function args
    using Functor_glGetSamplerParameter                         = glFunctor<>; // TODO: add function args
    using Functor_glGetShader                                   = glFunctor<>; // TODO: add function args
    using Functor_glGetShaderInfoLog                            = glFunctor<>; // TODO: add function args
    using Functor_glGetShaderPrecisionFormat                    = glFunctor<>; // TODO: add function args
    using Functor_glGetShaderSource                             = glFunctor<>; // TODO: add function args
    using Functor_glGetString                                   = glFunctor<>; // TODO: add function args
    using Functor_glGetStringi                                  = glFunctor<>; // TODO: add function args
    using Functor_glGetSubroutineIndex                          = glFunctor<>; // TODO: add function args
    using Functor_glGetSubroutineUniformLocation                = glFunctor<>; // TODO: add function args
    using Functor_glGetSync                                     = glFunctor<>; // TODO: add function args
    using Functor_glGetTexImage                                 = glFunctor<>; // TODO: add function args
    using Functor_glGetTexLevelParameter                        = glFunctor<>; // TODO: add function args
    using Functor_glGetTexParameter                             = glFunctor<>; // TODO: add function args
    using Functor_glGetTransformFeedbackVarying                 = glFunctor<>; // TODO: add function args
    using Functor_glGetUniform                                  = glFunctor<>; // TODO: add function args
    using Functor_glGetUniformBlockIndex                        = glFunctor<>; // TODO: add function args
    using Functor_glGetUniformIndices                           = glFunctor<>; // TODO: add function args
    using Functor_glGetUniformLocation                          = glFunctor<>; // TODO: add function args
    using Functor_glGetUniformSubroutine                        = glFunctor<>; // TODO: add function args
    using Functor_glGetVertexAttrib                             = glFunctor<>; // TODO: add function args
    using Functor_glGetVertexAttribPointer                      = glFunctor<>; // TODO: add function args
    using Functor_glHint                                        = glFunctor<>; // TODO: add function args
    using Functor_glInvalidateBufferData                        = glFunctor<>; // TODO: add function args
    using Functor_glInvalidateBufferSubData                     = glFunctor<>; // TODO: add function args
    using Functor_glInvalidateFramebuffer                       = glFunctor<>; // TODO: add function args
    using Functor_glInvalidateSubFramebuffer                    = glFunctor<>; // TODO: add function args
    using Functor_glInvalidateTexImage                          = glFunctor<>; // TODO: add function args
    using Functor_glInvalidateTexSubImage                       = glFunctor<>; // TODO: add function args
    using Functor_glIsBuffer                                    = glFunctor<>; // TODO: add function args
    using Functor_glIsEnabled                                   = glFunctor<>; // TODO: add function args
    using Functor_glIsFramebuffer                               = glFunctor<>; // TODO: add function args
    using Functor_glIsProgram                                   = glFunctor<>; // TODO: add function args
    using Functor_glIsProgramPipeline                           = glFunctor<>; // TODO: add function args
    using Functor_glIsQuery                                     = glFunctor<>; // TODO: add function args
    using Functor_glIsRenderbuffer                              = glFunctor<>; // TODO: add function args
    using Functor_glIsSampler                                   = glFunctor<>; // TODO: add function args
    using Functor_glIsShader                                    = glFunctor<>; // TODO: add function args
    using Functor_glIsSync                                      = glFunctor<>; // TODO: add function args
    using Functor_glIsTexture                                   = glFunctor<>; // TODO: add function args
    using Functor_glIsTransformFeedback                         = glFunctor<>; // TODO: add function args
    using Functor_glIsVertexArray                               = glFunctor<>; // TODO: add function args
    using Functor_glLineWidth                                   = glFunctor<>; // TODO: add function args
    using Functor_glLinkProgram                                 = glFunctor<>; // TODO: add function args
    using Functor_glLogicOp                                     = glFunctor<>; // TODO: add function args
    using Functor_glMapBuffer                                   = glFunctor<>; // TODO: add function args
    using Functor_glMapBufferRange                              = glFunctor<>; // TODO: add function args
    using Functor_glMemoryBarrier                               = glFunctor<>; // TODO: add function args
    using Functor_glMinSampleShading                            = glFunctor<>; // TODO: add function args
    using Functor_glMultiDrawArrays                             = glFunctor<>; // TODO: add function args
    using Functor_glMultiDrawArraysIndirect                     = glFunctor<>; // TODO: add function args
    using Functor_glMultiDrawElements                           = glFunctor<>; // TODO: add function args
    using Functor_glMultiDrawElementsBaseVertex                 = glFunctor<>; // TODO: add function args
    using Functor_glMultiDrawElementsIndirect                   = glFunctor<>; // TODO: add function args
    using Functor_glObjectLabel                                 = glFunctor<>; // TODO: add function args
    using Functor_glObjectPtrLabel                              = glFunctor<>; // TODO: add function args
    using Functor_glPatchParameter                              = glFunctor<>; // TODO: add function args
    using Functor_glPauseTransformFeedback                      = glFunctor<>; // TODO: add function args
    using Functor_glPixelStore                                  = glFunctor<>; // TODO: add function args
    using Functor_glPointParameter                              = glFunctor<>; // TODO: add function args
    using Functor_glPointSize                                   = glFunctor<>; // TODO: add function args
    using Functor_glPolygonMode                                 = glFunctor<>; // TODO: add function args
    using Functor_glPolygonOffset                               = glFunctor<>; // TODO: add function args
    using Functor_glPopDebugGroup                               = glFunctor<>; // TODO: add function args
    using Functor_glPrimitiveRestartIndex                       = glFunctor<>; // TODO: add function args
    using Functor_glProgramBinary                               = glFunctor<>; // TODO: add function args
    using Functor_glProgramParameter                            = glFunctor<>; // TODO: add function args
    using Functor_glProgramUniform                              = glFunctor<>; // TODO: add function args
    using Functor_glProgramUniformMatrix                        = glFunctor<>; // TODO: add function args
    using Functor_glProvokingVertex                             = glFunctor<>; // TODO: add function args
    using Functor_glPushDebugGroup                              = glFunctor<>; // TODO: add function args
    using Functor_glQueryCounter                                = glFunctor<>; // TODO: add function args
    using Functor_glReadBuffer                                  = glFunctor<>; // TODO: add function args
    using Functor_glReadPixels                                  = glFunctor<>; // TODO: add function args
    using Functor_glReleaseShaderCompiler                       = glFunctor<>; // TODO: add function args
    using Functor_glRenderbufferStorage                         = glFunctor<>; // TODO: add function args
    using Functor_glRenderbufferStorageMultisample              = glFunctor<>; // TODO: add function args
    using Functor_glResumeTransformFeedback                     = glFunctor<>; // TODO: add function args
    using Functor_glSampleCoverage                              = glFunctor<>; // TODO: add function args
    using Functor_glSampleMask                                  = glFunctor<>; // TODO: add function args
    using Functor_glSamplerParameter                            = glFunctor<>; // TODO: add function args
    using Functor_glScissor                                     = glFunctor<>; // TODO: add function args
    using Functor_glScissorArray                                = glFunctor<>; // TODO: add function args
    using Functor_glScissorIndexed                              = glFunctor<>; // TODO: add function args
    using Functor_glShaderBinary                                = glFunctor<>; // TODO: add function args
    using Functor_glShaderSource                                = glFunctor<>; // TODO: add function args
    using Functor_glShaderStorageBlockBinding                   = glFunctor<>; // TODO: add function args
    using Functor_glStencilFunc                                 = glFunctor<>; // TODO: add function args
    using Functor_glStencilFuncSeparate                         = glFunctor<>; // TODO: add function args
    using Functor_glStencilMask                                 = glFunctor<>; // TODO: add function args
    using Functor_glStencilMaskSeparate                         = glFunctor<>; // TODO: add function args
    using Functor_glStencilOp                                   = glFunctor<>; // TODO: add function args
    using Functor_glStencilOpSeparate                           = glFunctor<>; // TODO: add function args
    using Functor_glTexBuffer                                   = glFunctor<>; // TODO: add function args
    using Functor_glTexBufferRange                              = glFunctor<>; // TODO: add function args
    using Functor_glTexImage1D                                  = glFunctor<>; // TODO: add function args
    using Functor_glTexImage2D                                  = glFunctor<>; // TODO: add function args
    using Functor_glTexImage2DMultisample                       = glFunctor<>; // TODO: add function args
    using Functor_glTexImage3D                                  = glFunctor<>; // TODO: add function args
    using Functor_glTexImage3DMultisample                       = glFunctor<>; // TODO: add function args
    using Functor_glTexParameter                                = glFunctor<>; // TODO: add function args
    using Functor_glTexStorage1D                                = glFunctor<>; // TODO: add function args
    using Functor_glTexStorage2D                                = glFunctor<>; // TODO: add function args
    using Functor_glTexStorage2DMultisample                     = glFunctor<>; // TODO: add function args
    using Functor_glTexStorage3D                                = glFunctor<>; // TODO: add function args
    using Functor_glTexStorage3DMultisample                     = glFunctor<>; // TODO: add function args
    using Functor_glTexSubImage1D                               = glFunctor<>; // TODO: add function args
    using Functor_glTexSubImage2D                               = glFunctor<>; // TODO: add function args
    using Functor_glTexSubImage3D                               = glFunctor<>; // TODO: add function args
    using Functor_glTextureView                                 = glFunctor<>; // TODO: add function args
    using Functor_glTransformFeedbackVaryings                   = glFunctor<>; // TODO: add function args
    using Functor_glUniform                                     = glFunctor<>; // TODO: add function args
    using Functor_glUniformBlockBinding                         = glFunctor<>; // TODO: add function args
    using Functor_glUniformMatrix                               = glFunctor<>; // TODO: add function args
    using Functor_glUniformSubroutines                          = glFunctor<>; // TODO: add function args
    using Functor_glUnmapBuffer                                 = glFunctor<>; // TODO: add function args
    using Functor_glUseProgram                                  = glFunctor<>; // TODO: add function args
    using Functor_glUseProgramStages                            = glFunctor<>; // TODO: add function args
    using Functor_glValidateProgram                             = glFunctor<>; // TODO: add function args
    using Functor_glValidateProgramPipeline                     = glFunctor<>; // TODO: add function args
    using Functor_glVertexAttrib                                = glFunctor<>; // TODO: add function args
    using Functor_glVertexAttribBinding                         = glFunctor<>; // TODO: add function args
    using Functor_glVertexAttribDivisor                         = glFunctor<>; // TODO: add function args
    using Functor_glVertexAttribFormat                          = glFunctor<>; // TODO: add function args
    using Functor_glVertexAttribIFormat                         = glFunctor<>; // TODO: add function args
    using Functor_glVertexAttribIPointer                        = glFunctor<>; // TODO: add function args
    using Functor_glVertexAttribLFormat                         = glFunctor<>; // TODO: add function args
    using Functor_glVertexAttribLPointer                        = glFunctor<>; // TODO: add function args
    using Functor_glVertexAttribPointer                         = glFunctor<>; // TODO: add function args
    using Functor_glVertexBindingDivisor                        = glFunctor<>; // TODO: add function args
    using Functor_glViewport                                    = glFunctor<>; // TODO: add function args
    using Functor_glViewportArray                               = glFunctor<>; // TODO: add function args
    using Functor_glViewportIndexed                             = glFunctor<>; // TODO: add function args
    using Functor_glWaitSync                                    = glFunctor<>; // TODO: add function args
    // clang-format on
  public: // api

    glLoadContext(
            glfw::wrap::Window                               *window,
            std::function<Func_glAnyProc *(std::string_view)> gl_load_proc = [](std::string_view proc_name) -> Func_glAnyProc *
            {
                return (Func_glAnyProc *)glfw::wrap::get_proc_address(proc_name.data());
            }
    )
        : context_(window)
    {
        ActiveShaderProgram                         = Functor_glActiveShaderProgram("glActiveShaderProgram", gl_load_proc);
        ActiveTexture                               = Functor_glActiveTexture("glActiveTexture", gl_load_proc);
        AttachShader                                = Functor_glAttachShader("glAttachShader", gl_load_proc);
        BeginConditionalRender                      = Functor_glBeginConditionalRender("glBeginConditionalRender", gl_load_proc);
        BeginQuery                                  = Functor_glBeginQuery("glBeginQuery", gl_load_proc);
        BeginQueryIndexed                           = Functor_glBeginQueryIndexed("glBeginQueryIndexed", gl_load_proc);
        BeginTransformFeedback                      = Functor_glBeginTransformFeedback("glBeginTransformFeedback", gl_load_proc);
        BindAttribLocation                          = Functor_glBindAttribLocation("glBindAttribLocation", gl_load_proc);
        BindBuffer                                  = Functor_glBindBuffer("glBindBuffer", gl_load_proc);
        BindBufferBase                              = Functor_glBindBufferBase("glBindBufferBase", gl_load_proc);
        BindBufferRange                             = Functor_glBindBufferRange("glBindBufferRange", gl_load_proc);
        BindBuffersBase                             = Functor_glBindBuffersBase("glBindBuffersBase", gl_load_proc);
        BindBuffersRange                            = Functor_glBindBuffersRange("glBindBuffersRange", gl_load_proc);
        BindFragDataLocation                        = Functor_glBindFragDataLocation("glBindFragDataLocation", gl_load_proc);
        BindFragDataLocationIndexed                 = Functor_glBindFragDataLocationIndexed("glBindFragDataLocationIndexed", gl_load_proc);
        BindFramebuffer                             = Functor_glBindFramebuffer("glBindFramebuffer", gl_load_proc);
        BindImageTexture                            = Functor_glBindImageTexture("glBindImageTexture", gl_load_proc);
        BindImageTextures                           = Functor_glBindImageTextures("glBindImageTextures", gl_load_proc);
        BindProgramPipeline                         = Functor_glBindProgramPipeline("glBindProgramPipeline", gl_load_proc);
        BindRenderbuffer                            = Functor_glBindRenderbuffer("glBindRenderbuffer", gl_load_proc);
        BindSampler                                 = Functor_glBindSampler("glBindSampler", gl_load_proc);
        BindSamplers                                = Functor_glBindSamplers("glBindSamplers", gl_load_proc);
        BindTexture                                 = Functor_glBindTexture("glBindTexture", gl_load_proc);
        BindTextures                                = Functor_glBindTextures("glBindTextures", gl_load_proc);
        BindTransformFeedback                       = Functor_glBindTransformFeedback("glBindTransformFeedback", gl_load_proc);
        BindVertexArray                             = Functor_glBindVertexArray("glBindVertexArray", gl_load_proc);
        BindVertexBuffer                            = Functor_glBindVertexBuffer("glBindVertexBuffer", gl_load_proc);
        BlendColor                                  = Functor_glBlendColor("glBlendColor", gl_load_proc);
        BlendEquation                               = Functor_glBlendEquation("glBlendEquation", gl_load_proc);
        BlendEquationSeparate                       = Functor_glBlendEquationSeparate("glBlendEquationSeparate", gl_load_proc);
        BlendFunc                                   = Functor_glBlendFunc("glBlendFunc", gl_load_proc);
        BlendFuncSeparate                           = Functor_glBlendFuncSeparate("glBlendFuncSeparate", gl_load_proc);
        BlendFuncSeparatei                          = Functor_glBlendFuncSeparatei("glBlendFuncSeparatei", gl_load_proc);
        BlitFramebuffer                             = Functor_glBlitFramebuffer("glBlitFramebuffer", gl_load_proc);
        BufferData                                  = Functor_glBufferData("glBufferData", gl_load_proc);
        BufferStorage                               = Functor_glBufferStorage("glBufferStorage", gl_load_proc);
        BufferSubData                               = Functor_glBufferSubData("glBufferSubData", gl_load_proc);
        CheckFramebufferStatus                      = Functor_glCheckFramebufferStatus("glCheckFramebufferStatus", gl_load_proc);
        ClampColor                                  = Functor_glClampColor("glClampColor", gl_load_proc);
        Clear                                       = Functor_glClear("glClear", gl_load_proc);
        ClearBuffer                                 = Functor_glClearBuffer("glClearBuffer", gl_load_proc);
        ClearBufferData                             = Functor_glClearBufferData("glClearBufferData", gl_load_proc);
        ClearBufferSubData                          = Functor_glClearBufferSubData("glClearBufferSubData", gl_load_proc);
        ClearColor                                  = Functor_glClearColor("glClearColor", gl_load_proc);
        ClearDepth                                  = Functor_glClearDepth("glClearDepth", gl_load_proc);
        ClearStencil                                = Functor_glClearStencil("glClearStencil", gl_load_proc);
        ClearTexImage                               = Functor_glClearTexImage("glClearTexImage", gl_load_proc);
        ClearTexSubImage                            = Functor_glClearTexSubImage("glClearTexSubImage", gl_load_proc);
        ClientWaitSync                              = Functor_glClientWaitSync("glClientWaitSync", gl_load_proc);
        ColorMask                                   = Functor_glColorMask("glColorMask", gl_load_proc);
        CompileShader                               = Functor_glCompileShader("glCompileShader", gl_load_proc);
        CompressedTexImage1D                        = Functor_glCompressedTexImage1D("glCompressedTexImage1D", gl_load_proc);
        CompressedTexImage2D                        = Functor_glCompressedTexImage2D("glCompressedTexImage2D", gl_load_proc);
        CompressedTexImage3D                        = Functor_glCompressedTexImage3D("glCompressedTexImage3D", gl_load_proc);
        CompressedTexSubImage1D                     = Functor_glCompressedTexSubImage1D("glCompressedTexSubImage1D", gl_load_proc);
        CompressedTexSubImage2D                     = Functor_glCompressedTexSubImage2D("glCompressedTexSubImage2D", gl_load_proc);
        CompressedTexSubImage3D                     = Functor_glCompressedTexSubImage3D("glCompressedTexSubImage3D", gl_load_proc);
        CopyBufferSubData                           = Functor_glCopyBufferSubData("glCopyBufferSubData", gl_load_proc);
        CopyImageSubData                            = Functor_glCopyImageSubData("glCopyImageSubData", gl_load_proc);
        CopyTexImage1D                              = Functor_glCopyTexImage1D("glCopyTexImage1D", gl_load_proc);
        CopyTexImage2D                              = Functor_glCopyTexImage2D("glCopyTexImage2D", gl_load_proc);
        CopyTexSubImage1D                           = Functor_glCopyTexSubImage1D("glCopyTexSubImage1D", gl_load_proc);
        CopyTexSubImage2D                           = Functor_glCopyTexSubImage2D("glCopyTexSubImage2D", gl_load_proc);
        CopyTexSubImage3D                           = Functor_glCopyTexSubImage3D("glCopyTexSubImage3D", gl_load_proc);
        BindVertexBuffers                           = Functor_glBindVertexBuffers("glBindVertexBuffers", gl_load_proc);
        CreateProgram                               = Functor_glCreateProgram("glCreateProgram", gl_load_proc);
        CreateShader                                = Functor_glCreateShader("glCreateShader", gl_load_proc);
        CreateShaderProgram                         = Functor_glCreateShaderProgram("glCreateShaderProgram", gl_load_proc);
        CreateShaderProgramv                        = Functor_glCreateShaderProgramv("glCreateShaderProgramv", gl_load_proc);
        CullFace                                    = Functor_glCullFace("glCullFace", gl_load_proc);
        DebugMessageCallback                        = Functor_glDebugMessageCallback("glDebugMessageCallback", gl_load_proc);
        DebugMessageControl                         = Functor_glDebugMessageControl("glDebugMessageControl", gl_load_proc);
        DebugMessageInsert                          = Functor_glDebugMessageInsert("glDebugMessageInsert", gl_load_proc);
        DeleteBuffers                               = Functor_glDeleteBuffers("glDeleteBuffers", gl_load_proc);
        DeleteFramebuffers                          = Functor_glDeleteFramebuffers("glDeleteFramebuffers", gl_load_proc);
        DeleteProgram                               = Functor_glDeleteProgram("glDeleteProgram", gl_load_proc);
        DeleteProgramPipelines                      = Functor_glDeleteProgramPipelines("glDeleteProgramPipelines", gl_load_proc);
        DeleteQueries                               = Functor_glDeleteQueries("glDeleteQueries", gl_load_proc);
        DeleteRenderbuffers                         = Functor_glDeleteRenderbuffers("glDeleteRenderbuffers", gl_load_proc);
        DeleteSamplers                              = Functor_glDeleteSamplers("glDeleteSamplers", gl_load_proc);
        DeleteShader                                = Functor_glDeleteShader("glDeleteShader", gl_load_proc);
        DeleteSync                                  = Functor_glDeleteSync("glDeleteSync", gl_load_proc);
        DeleteTextures                              = Functor_glDeleteTextures("glDeleteTextures", gl_load_proc);
        DeleteTransformFeedbacks                    = Functor_glDeleteTransformFeedbacks("glDeleteTransformFeedbacks", gl_load_proc);
        DeleteVertexArrays                          = Functor_glDeleteVertexArrays("glDeleteVertexArrays", gl_load_proc);
        DepthFunc                                   = Functor_glDepthFunc("glDepthFunc", gl_load_proc);
        DepthMask                                   = Functor_glDepthMask("glDepthMask", gl_load_proc);
        DepthRange                                  = Functor_glDepthRange("glDepthRange", gl_load_proc);
        DepthRangeArray                             = Functor_glDepthRangeArray("glDepthRangeArray", gl_load_proc);
        DepthRangeIndexed                           = Functor_glDepthRangeIndexed("glDepthRangeIndexed", gl_load_proc);
        DetachShader                                = Functor_glDetachShader("glDetachShader", gl_load_proc);
        Disable                                     = Functor_glDisable("glDisable", gl_load_proc);
        Disablei                                    = Functor_glDisablei("glDisablei", gl_load_proc);
        DisableVertexAttribArray                    = Functor_glDisableVertexAttribArray("glDisableVertexAttribArray", gl_load_proc);
        DispatchCompute                             = Functor_glDispatchCompute("glDispatchCompute", gl_load_proc);
        DispatchComputeIndirect                     = Functor_glDispatchComputeIndirect("glDispatchComputeIndirect", gl_load_proc);
        DrawArrays                                  = Functor_glDrawArrays("glDrawArrays", gl_load_proc);
        DrawArraysIndirect                          = Functor_glDrawArraysIndirect("glDrawArraysIndirect", gl_load_proc);
        DrawArraysInstanced                         = Functor_glDrawArraysInstanced("glDrawArraysInstanced", gl_load_proc);
        DrawArraysInstancedBaseInstance             = Functor_glDrawArraysInstancedBaseInstance("glDrawArraysInstancedBaseInstance", gl_load_proc);
        DrawBuffer                                  = Functor_glDrawBuffer("glDrawBuffer", gl_load_proc);
        DrawBuffers                                 = Functor_glDrawBuffers("glDrawBuffers", gl_load_proc);
        DrawElements                                = Functor_glDrawElements("glDrawElements", gl_load_proc);
        DrawElementsBaseVertex                      = Functor_glDrawElementsBaseVertex("glDrawElementsBaseVertex", gl_load_proc);
        DrawElementsIndirect                        = Functor_glDrawElementsIndirect("glDrawElementsIndirect", gl_load_proc);
        DrawElementsInstanced                       = Functor_glDrawElementsInstanced("glDrawElementsInstanced", gl_load_proc);
        DrawElementsInstancedBaseInstance           = Functor_glDrawElementsInstancedBaseInstance("glDrawElementsInstancedBaseInstance", gl_load_proc);
        DrawElementsInstancedBaseVertex             = Functor_glDrawElementsInstancedBaseVertex("glDrawElementsInstancedBaseVertex", gl_load_proc);
        DrawElementsInstancedBaseVertexBaseInstance = Functor_glDrawElementsInstancedBaseVertexBaseInstance("glDrawElementsInstancedBaseVertexBaseInstance", gl_load_proc);
        DrawRangeElements                           = Functor_glDrawRangeElements("glDrawRangeElements", gl_load_proc);
        DrawRangeElementsBaseVertex                 = Functor_glDrawRangeElementsBaseVertex("glDrawRangeElementsBaseVertex", gl_load_proc);
        DrawTransformFeedback                       = Functor_glDrawTransformFeedback("glDrawTransformFeedback", gl_load_proc);
        DrawTransformFeedbackInstanced              = Functor_glDrawTransformFeedbackInstanced("glDrawTransformFeedbackInstanced", gl_load_proc);
        DrawTransformFeedbackStream                 = Functor_glDrawTransformFeedbackStream("glDrawTransformFeedbackStream", gl_load_proc);
        DrawTransformFeedbackStreamInstanced        = Functor_glDrawTransformFeedbackStreamInstanced("glDrawTransformFeedbackStreamInstanced", gl_load_proc);
        Enable                                      = Functor_glEnable("glEnable", gl_load_proc);
        Enablei                                     = Functor_glEnablei("glEnablei", gl_load_proc);
        EnableVertexAttribArray                     = Functor_glEnableVertexAttribArray("glEnableVertexAttribArray", gl_load_proc);
        EndConditionalRender                        = Functor_glEndConditionalRender("glEndConditionalRender", gl_load_proc);
        EndQuery                                    = Functor_glEndQuery("glEndQuery", gl_load_proc);
        EndQueryIndexed                             = Functor_glEndQueryIndexed("glEndQueryIndexed", gl_load_proc);
        EndTransformFeedback                        = Functor_glEndTransformFeedback("glEndTransformFeedback", gl_load_proc);
        FenceSync                                   = Functor_glFenceSync("glFenceSync", gl_load_proc);
        Finish                                      = Functor_glFinish("glFinish", gl_load_proc);
        Flush                                       = Functor_glFlush("glFlush", gl_load_proc);
        FlushMappedBufferRange                      = Functor_glFlushMappedBufferRange("glFlushMappedBufferRange", gl_load_proc);
        FramebufferParameter                        = Functor_glFramebufferParameter("glFramebufferParameter", gl_load_proc);
        FramebufferParameteri                       = Functor_glFramebufferParameteri("glFramebufferParameteri", gl_load_proc);
        FramebufferRenderbuffer                     = Functor_glFramebufferRenderbuffer("glFramebufferRenderbuffer", gl_load_proc);
        FramebufferTexture                          = Functor_glFramebufferTexture("glFramebufferTexture", gl_load_proc);
        FramebufferTexture1D                        = Functor_glFramebufferTexture1D("glFramebufferTexture1D", gl_load_proc);
        FramebufferTexture2D                        = Functor_glFramebufferTexture2D("glFramebufferTexture2D", gl_load_proc);
        FramebufferTexture3D                        = Functor_glFramebufferTexture3D("glFramebufferTexture3D", gl_load_proc);
        FramebufferTextureLayer                     = Functor_glFramebufferTextureLayer("glFramebufferTextureLayer", gl_load_proc);
        FrontFace                                   = Functor_glFrontFace("glFrontFace", gl_load_proc);
        GenBuffers                                  = Functor_glGenBuffers("glGenBuffers", gl_load_proc);
        GenerateMipmap                              = Functor_glGenerateMipmap("glGenerateMipmap", gl_load_proc);
        GenFramebuffers                             = Functor_glGenFramebuffers("glGenFramebuffers", gl_load_proc);
        GenProgramPipelines                         = Functor_glGenProgramPipelines("glGenProgramPipelines", gl_load_proc);
        GenQueries                                  = Functor_glGenQueries("glGenQueries", gl_load_proc);
        GenRenderbuffers                            = Functor_glGenRenderbuffers("glGenRenderbuffers", gl_load_proc);
        GenSamplers                                 = Functor_glGenSamplers("glGenSamplers", gl_load_proc);
        GenTextures                                 = Functor_glGenTextures("glGenTextures", gl_load_proc);
        GenTransformFeedbacks                       = Functor_glGenTransformFeedbacks("glGenTransformFeedbacks", gl_load_proc);
        GenVertexArrays                             = Functor_glGenVertexArrays("glGenVertexArrays", gl_load_proc);
        Get                                         = Functor_glGet("glGet", gl_load_proc);
        GetBooleanv                                 = Functor_glGetBooleanv("glGetBooleanv", gl_load_proc);
        GetDoublev                                  = Functor_glGetDoublev("glGetDoublev", gl_load_proc);
        GetFloatv                                   = Functor_glGetFloatv("glGetFloatv", gl_load_proc);
        GetInteger64v                               = Functor_glGetInteger64v("glGetInteger64v", gl_load_proc);
        GetIntegerv                                 = Functor_glGetIntegerv("glGetIntegerv", gl_load_proc);
        GetActiveAtomicCounterBuffer                = Functor_glGetActiveAtomicCounterBuffer("glGetActiveAtomicCounterBuffer", gl_load_proc);
        GetActiveAtomicCounterBufferiv              = Functor_glGetActiveAtomicCounterBufferiv("glGetActiveAtomicCounterBufferiv", gl_load_proc);
        GetActiveAttrib                             = Functor_glGetActiveAttrib("glGetActiveAttrib", gl_load_proc);
        GetActiveSubroutineName                     = Functor_glGetActiveSubroutineName("glGetActiveSubroutineName", gl_load_proc);
        GetActiveSubroutineUniform                  = Functor_glGetActiveSubroutineUniform("glGetActiveSubroutineUniform", gl_load_proc);
        GetActiveSubroutineUniformName              = Functor_glGetActiveSubroutineUniformName("glGetActiveSubroutineUniformName", gl_load_proc);
        GetActiveUniform                            = Functor_glGetActiveUniform("glGetActiveUniform", gl_load_proc);
        GetActiveUniformBlock                       = Functor_glGetActiveUniformBlock("glGetActiveUniformBlock", gl_load_proc);
        GetActiveUniformBlockName                   = Functor_glGetActiveUniformBlockName("glGetActiveUniformBlockName", gl_load_proc);
        GetActiveUniformName                        = Functor_glGetActiveUniformName("glGetActiveUniformName", gl_load_proc);
        GetActiveUniforms                           = Functor_glGetActiveUniforms("glGetActiveUniforms", gl_load_proc);
        GetActiveUniformsiv                         = Functor_glGetActiveUniformsiv("glGetActiveUniformsiv", gl_load_proc);
        GetAttachedShaders                          = Functor_glGetAttachedShaders("glGetAttachedShaders", gl_load_proc);
        GetAttribLocation                           = Functor_glGetAttribLocation("glGetAttribLocation", gl_load_proc);
        GetBufferParameter                          = Functor_glGetBufferParameter("glGetBufferParameter", gl_load_proc);
        GetBufferPointer                            = Functor_glGetBufferPointer("glGetBufferPointer", gl_load_proc);
        GetBufferSubData                            = Functor_glGetBufferSubData("glGetBufferSubData", gl_load_proc);
        GetCompressedTexImage                       = Functor_glGetCompressedTexImage("glGetCompressedTexImage", gl_load_proc);
        GetDebugMessageLog                          = Functor_glGetDebugMessageLog("glGetDebugMessageLog", gl_load_proc);
        GetError                                    = Functor_glGetError("glGetError", gl_load_proc);
        GetFragDataIndex                            = Functor_glGetFragDataIndex("glGetFragDataIndex", gl_load_proc);
        GetFragDataLocation                         = Functor_glGetFragDataLocation("glGetFragDataLocation", gl_load_proc);
        GetFramebufferAttachmentParameter           = Functor_glGetFramebufferAttachmentParameter("glGetFramebufferAttachmentParameter", gl_load_proc);
        GetFramebufferParameter                     = Functor_glGetFramebufferParameter("glGetFramebufferParameter", gl_load_proc);
        GetFramebufferParameteriv                   = Functor_glGetFramebufferParameteriv("glGetFramebufferParameteriv", gl_load_proc);
        GetInternalformat                           = Functor_glGetInternalformat("glGetInternalformat", gl_load_proc);
        GetMultisample                              = Functor_glGetMultisample("glGetMultisample", gl_load_proc);
        GetObjectLabel                              = Functor_glGetObjectLabel("glGetObjectLabel", gl_load_proc);
        GetObjectPtrLabel                           = Functor_glGetObjectPtrLabel("glGetObjectPtrLabel", gl_load_proc);
        GetProgram                                  = Functor_glGetProgram("glGetProgram", gl_load_proc);
        GetProgramBinary                            = Functor_glGetProgramBinary("glGetProgramBinary", gl_load_proc);
        GetProgramInfoLog                           = Functor_glGetProgramInfoLog("glGetProgramInfoLog", gl_load_proc);
        GetProgramInterface                         = Functor_glGetProgramInterface("glGetProgramInterface", gl_load_proc);
        GetProgramPipeline                          = Functor_glGetProgramPipeline("glGetProgramPipeline", gl_load_proc);
        GetProgramPipelineInfoLog                   = Functor_glGetProgramPipelineInfoLog("glGetProgramPipelineInfoLog", gl_load_proc);
        GetProgramResource                          = Functor_glGetProgramResource("glGetProgramResource", gl_load_proc);
        GetProgramResourceLocation                  = Functor_glGetProgramResourceLocation("glGetProgramResourceLocation", gl_load_proc);
        GetProgramResourceLocationIndex             = Functor_glGetProgramResourceLocationIndex("glGetProgramResourceLocationIndex", gl_load_proc);
        GetProgramResourceIndex                     = Functor_glGetProgramResourceIndex("glGetProgramResourceIndex", gl_load_proc);
        GetProgramResourceName                      = Functor_glGetProgramResourceName("glGetProgramResourceName", gl_load_proc);
        GetProgramStage                             = Functor_glGetProgramStage("glGetProgramStage", gl_load_proc);
        GetQuery                                    = Functor_glGetQuery("glGetQuery", gl_load_proc);
        GetQueryIndexed                             = Functor_glGetQueryIndexed("glGetQueryIndexed", gl_load_proc);
        GetQueryObject                              = Functor_glGetQueryObject("glGetQueryObject", gl_load_proc);
        GetRenderbufferParameter                    = Functor_glGetRenderbufferParameter("glGetRenderbufferParameter", gl_load_proc);
        GetSamplerParameter                         = Functor_glGetSamplerParameter("glGetSamplerParameter", gl_load_proc);
        GetShader                                   = Functor_glGetShader("glGetShader", gl_load_proc);
        GetShaderInfoLog                            = Functor_glGetShaderInfoLog("glGetShaderInfoLog", gl_load_proc);
        GetShaderPrecisionFormat                    = Functor_glGetShaderPrecisionFormat("glGetShaderPrecisionFormat", gl_load_proc);
        GetShaderSource                             = Functor_glGetShaderSource("glGetShaderSource", gl_load_proc);
        GetString                                   = Functor_glGetString("glGetString", gl_load_proc);
        GetStringi                                  = Functor_glGetStringi("glGetStringi", gl_load_proc);
        GetSubroutineIndex                          = Functor_glGetSubroutineIndex("glGetSubroutineIndex", gl_load_proc);
        GetSubroutineUniformLocation                = Functor_glGetSubroutineUniformLocation("glGetSubroutineUniformLocation", gl_load_proc);
        GetSync                                     = Functor_glGetSync("glGetSync", gl_load_proc);
        GetTexImage                                 = Functor_glGetTexImage("glGetTexImage", gl_load_proc);
        GetTexLevelParameter                        = Functor_glGetTexLevelParameter("glGetTexLevelParameter", gl_load_proc);
        GetTexParameter                             = Functor_glGetTexParameter("glGetTexParameter", gl_load_proc);
        GetTransformFeedbackVarying                 = Functor_glGetTransformFeedbackVarying("glGetTransformFeedbackVarying", gl_load_proc);
        GetUniform                                  = Functor_glGetUniform("glGetUniform", gl_load_proc);
        GetUniformBlockIndex                        = Functor_glGetUniformBlockIndex("glGetUniformBlockIndex", gl_load_proc);
        GetUniformIndices                           = Functor_glGetUniformIndices("glGetUniformIndices", gl_load_proc);
        GetUniformLocation                          = Functor_glGetUniformLocation("glGetUniformLocation", gl_load_proc);
        GetUniformSubroutine                        = Functor_glGetUniformSubroutine("glGetUniformSubroutine", gl_load_proc);
        GetVertexAttrib                             = Functor_glGetVertexAttrib("glGetVertexAttrib", gl_load_proc);
        GetVertexAttribPointer                      = Functor_glGetVertexAttribPointer("glGetVertexAttribPointer", gl_load_proc);
        Hint                                        = Functor_glHint("glHint", gl_load_proc);
        InvalidateBufferData                        = Functor_glInvalidateBufferData("glInvalidateBufferData", gl_load_proc);
        InvalidateBufferSubData                     = Functor_glInvalidateBufferSubData("glInvalidateBufferSubData", gl_load_proc);
        InvalidateFramebuffer                       = Functor_glInvalidateFramebuffer("glInvalidateFramebuffer", gl_load_proc);
        InvalidateSubFramebuffer                    = Functor_glInvalidateSubFramebuffer("glInvalidateSubFramebuffer", gl_load_proc);
        InvalidateTexImage                          = Functor_glInvalidateTexImage("glInvalidateTexImage", gl_load_proc);
        InvalidateTexSubImage                       = Functor_glInvalidateTexSubImage("glInvalidateTexSubImage", gl_load_proc);
        IsBuffer                                    = Functor_glIsBuffer("glIsBuffer", gl_load_proc);
        IsEnabled                                   = Functor_glIsEnabled("glIsEnabled", gl_load_proc);
        IsFramebuffer                               = Functor_glIsFramebuffer("glIsFramebuffer", gl_load_proc);
        IsProgram                                   = Functor_glIsProgram("glIsProgram", gl_load_proc);
        IsProgramPipeline                           = Functor_glIsProgramPipeline("glIsProgramPipeline", gl_load_proc);
        IsQuery                                     = Functor_glIsQuery("glIsQuery", gl_load_proc);
        IsRenderbuffer                              = Functor_glIsRenderbuffer("glIsRenderbuffer", gl_load_proc);
        IsSampler                                   = Functor_glIsSampler("glIsSampler", gl_load_proc);
        IsShader                                    = Functor_glIsShader("glIsShader", gl_load_proc);
        IsSync                                      = Functor_glIsSync("glIsSync", gl_load_proc);
        IsTexture                                   = Functor_glIsTexture("glIsTexture", gl_load_proc);
        IsTransformFeedback                         = Functor_glIsTransformFeedback("glIsTransformFeedback", gl_load_proc);
        IsVertexArray                               = Functor_glIsVertexArray("glIsVertexArray", gl_load_proc);
        LineWidth                                   = Functor_glLineWidth("glLineWidth", gl_load_proc);
        LinkProgram                                 = Functor_glLinkProgram("glLinkProgram", gl_load_proc);
        LogicOp                                     = Functor_glLogicOp("glLogicOp", gl_load_proc);
        MapBuffer                                   = Functor_glMapBuffer("glMapBuffer", gl_load_proc);
        MapBufferRange                              = Functor_glMapBufferRange("glMapBufferRange", gl_load_proc);
        MemoryBarrier                               = Functor_glMemoryBarrier("glMemoryBarrier", gl_load_proc);
        MinSampleShading                            = Functor_glMinSampleShading("glMinSampleShading", gl_load_proc);
        MultiDrawArrays                             = Functor_glMultiDrawArrays("glMultiDrawArrays", gl_load_proc);
        MultiDrawArraysIndirect                     = Functor_glMultiDrawArraysIndirect("glMultiDrawArraysIndirect", gl_load_proc);
        MultiDrawElements                           = Functor_glMultiDrawElements("glMultiDrawElements", gl_load_proc);
        MultiDrawElementsBaseVertex                 = Functor_glMultiDrawElementsBaseVertex("glMultiDrawElementsBaseVertex", gl_load_proc);
        MultiDrawElementsIndirect                   = Functor_glMultiDrawElementsIndirect("glMultiDrawElementsIndirect", gl_load_proc);
        ObjectLabel                                 = Functor_glObjectLabel("glObjectLabel", gl_load_proc);
        ObjectPtrLabel                              = Functor_glObjectPtrLabel("glObjectPtrLabel", gl_load_proc);
        PatchParameter                              = Functor_glPatchParameter("glPatchParameter", gl_load_proc);
        PauseTransformFeedback                      = Functor_glPauseTransformFeedback("glPauseTransformFeedback", gl_load_proc);
        PixelStore                                  = Functor_glPixelStore("glPixelStore", gl_load_proc);
        PointParameter                              = Functor_glPointParameter("glPointParameter", gl_load_proc);
        PointSize                                   = Functor_glPointSize("glPointSize", gl_load_proc);
        PolygonMode                                 = Functor_glPolygonMode("glPolygonMode", gl_load_proc);
        PolygonOffset                               = Functor_glPolygonOffset("glPolygonOffset", gl_load_proc);
        PopDebugGroup                               = Functor_glPopDebugGroup("glPopDebugGroup", gl_load_proc);
        PrimitiveRestartIndex                       = Functor_glPrimitiveRestartIndex("glPrimitiveRestartIndex", gl_load_proc);
        ProgramBinary                               = Functor_glProgramBinary("glProgramBinary", gl_load_proc);
        ProgramParameter                            = Functor_glProgramParameter("glProgramParameter", gl_load_proc);
        ProgramUniform                              = Functor_glProgramUniform("glProgramUniform", gl_load_proc);
        ProgramUniformMatrix                        = Functor_glProgramUniformMatrix("glProgramUniformMatrix", gl_load_proc);
        ProvokingVertex                             = Functor_glProvokingVertex("glProvokingVertex", gl_load_proc);
        PushDebugGroup                              = Functor_glPushDebugGroup("glPushDebugGroup", gl_load_proc);
        QueryCounter                                = Functor_glQueryCounter("glQueryCounter", gl_load_proc);
        ReadBuffer                                  = Functor_glReadBuffer("glReadBuffer", gl_load_proc);
        ReadPixels                                  = Functor_glReadPixels("glReadPixels", gl_load_proc);
        ReleaseShaderCompiler                       = Functor_glReleaseShaderCompiler("glReleaseShaderCompiler", gl_load_proc);
        RenderbufferStorage                         = Functor_glRenderbufferStorage("glRenderbufferStorage", gl_load_proc);
        RenderbufferStorageMultisample              = Functor_glRenderbufferStorageMultisample("glRenderbufferStorageMultisample", gl_load_proc);
        ResumeTransformFeedback                     = Functor_glResumeTransformFeedback("glResumeTransformFeedback", gl_load_proc);
        SampleCoverage                              = Functor_glSampleCoverage("glSampleCoverage", gl_load_proc);
        SampleMask                                  = Functor_glSampleMask("glSampleMask", gl_load_proc);
        SamplerParameter                            = Functor_glSamplerParameter("glSamplerParameter", gl_load_proc);
        Scissor                                     = Functor_glScissor("glScissor", gl_load_proc);
        ScissorArray                                = Functor_glScissorArray("glScissorArray", gl_load_proc);
        ScissorIndexed                              = Functor_glScissorIndexed("glScissorIndexed", gl_load_proc);
        ShaderBinary                                = Functor_glShaderBinary("glShaderBinary", gl_load_proc);
        ShaderSource                                = Functor_glShaderSource("glShaderSource", gl_load_proc);
        ShaderStorageBlockBinding                   = Functor_glShaderStorageBlockBinding("glShaderStorageBlockBinding", gl_load_proc);
        StencilFunc                                 = Functor_glStencilFunc("glStencilFunc", gl_load_proc);
        StencilFuncSeparate                         = Functor_glStencilFuncSeparate("glStencilFuncSeparate", gl_load_proc);
        StencilMask                                 = Functor_glStencilMask("glStencilMask", gl_load_proc);
        StencilMaskSeparate                         = Functor_glStencilMaskSeparate("glStencilMaskSeparate", gl_load_proc);
        StencilOp                                   = Functor_glStencilOp("glStencilOp", gl_load_proc);
        StencilOpSeparate                           = Functor_glStencilOpSeparate("glStencilOpSeparate", gl_load_proc);
        TexBuffer                                   = Functor_glTexBuffer("glTexBuffer", gl_load_proc);
        TexBufferRange                              = Functor_glTexBufferRange("glTexBufferRange", gl_load_proc);
        TexImage1D                                  = Functor_glTexImage1D("glTexImage1D", gl_load_proc);
        TexImage2D                                  = Functor_glTexImage2D("glTexImage2D", gl_load_proc);
        TexImage2DMultisample                       = Functor_glTexImage2DMultisample("glTexImage2DMultisample", gl_load_proc);
        TexImage3D                                  = Functor_glTexImage3D("glTexImage3D", gl_load_proc);
        TexImage3DMultisample                       = Functor_glTexImage3DMultisample("glTexImage3DMultisample", gl_load_proc);
        TexParameter                                = Functor_glTexParameter("glTexParameter", gl_load_proc);
        TexStorage1D                                = Functor_glTexStorage1D("glTexStorage1D", gl_load_proc);
        TexStorage2D                                = Functor_glTexStorage2D("glTexStorage2D", gl_load_proc);
        TexStorage2DMultisample                     = Functor_glTexStorage2DMultisample("glTexStorage2DMultisample", gl_load_proc);
        TexStorage3D                                = Functor_glTexStorage3D("glTexStorage3D", gl_load_proc);
        TexStorage3DMultisample                     = Functor_glTexStorage3DMultisample("glTexStorage3DMultisample", gl_load_proc);
        TexSubImage1D                               = Functor_glTexSubImage1D("glTexSubImage1D", gl_load_proc);
        TexSubImage2D                               = Functor_glTexSubImage2D("glTexSubImage2D", gl_load_proc);
        TexSubImage3D                               = Functor_glTexSubImage3D("glTexSubImage3D", gl_load_proc);
        TextureView                                 = Functor_glTextureView("glTextureView", gl_load_proc);
        TransformFeedbackVaryings                   = Functor_glTransformFeedbackVaryings("glTransformFeedbackVaryings", gl_load_proc);
        Uniform                                     = Functor_glUniform("glUniform", gl_load_proc);
        UniformBlockBinding                         = Functor_glUniformBlockBinding("glUniformBlockBinding", gl_load_proc);
        UniformMatrix                               = Functor_glUniformMatrix("glUniformMatrix", gl_load_proc);
        UniformSubroutines                          = Functor_glUniformSubroutines("glUniformSubroutines", gl_load_proc);
        UnmapBuffer                                 = Functor_glUnmapBuffer("glUnmapBuffer", gl_load_proc);
        UseProgram                                  = Functor_glUseProgram("glUseProgram", gl_load_proc);
        UseProgramStages                            = Functor_glUseProgramStages("glUseProgramStages", gl_load_proc);
        ValidateProgram                             = Functor_glValidateProgram("glValidateProgram", gl_load_proc);
        ValidateProgramPipeline                     = Functor_glValidateProgramPipeline("glValidateProgramPipeline", gl_load_proc);
        VertexAttrib                                = Functor_glVertexAttrib("glVertexAttrib", gl_load_proc);
        VertexAttribBinding                         = Functor_glVertexAttribBinding("glVertexAttribBinding", gl_load_proc);
        VertexAttribDivisor                         = Functor_glVertexAttribDivisor("glVertexAttribDivisor", gl_load_proc);
        VertexAttribFormat                          = Functor_glVertexAttribFormat("glVertexAttribFormat", gl_load_proc);
        VertexAttribIFormat                         = Functor_glVertexAttribIFormat("glVertexAttribIFormat", gl_load_proc);
        VertexAttribIPointer                        = Functor_glVertexAttribIPointer("glVertexAttribIPointer", gl_load_proc);
        VertexAttribLFormat                         = Functor_glVertexAttribLFormat("glVertexAttribLFormat", gl_load_proc);
        VertexAttribLPointer                        = Functor_glVertexAttribLPointer("glVertexAttribLPointer", gl_load_proc);
        VertexAttribPointer                         = Functor_glVertexAttribPointer("glVertexAttribPointer", gl_load_proc);
        VertexBindingDivisor                        = Functor_glVertexBindingDivisor("glVertexBindingDivisor", gl_load_proc);
        Viewport                                    = Functor_glViewport("glViewport", gl_load_proc);
        ViewportArray                               = Functor_glViewportArray("glViewportArray", gl_load_proc);
        ViewportIndexed                             = Functor_glViewportIndexed("glViewportIndexed", gl_load_proc);
        WaitSync                                    = Functor_glWaitSync("glWaitSync", gl_load_proc);
    }

    glfw::wrap::Window *
    get()
    {
        return context_;
    }

    void
    make_current()
    {
        glfw::wrap::make_context_current(context_);
    }

  public: // wrapped opengl 4.6 funcs

    std::function<Functor_glActiveShaderProgram::glProcType>                         ActiveShaderProgram;
    std::function<Functor_glActiveTexture::glProcType>                               ActiveTexture;
    std::function<Functor_glAttachShader::glProcType>                                AttachShader;
    std::function<Functor_glBeginConditionalRender::glProcType>                      BeginConditionalRender;
    std::function<Functor_glBeginQuery::glProcType>                                  BeginQuery;
    std::function<Functor_glBeginQueryIndexed::glProcType>                           BeginQueryIndexed;
    std::function<Functor_glBeginTransformFeedback::glProcType>                      BeginTransformFeedback;
    std::function<Functor_glBindAttribLocation::glProcType>                          BindAttribLocation;
    std::function<Functor_glBindBuffer::glProcType>                                  BindBuffer;
    std::function<Functor_glBindBufferBase::glProcType>                              BindBufferBase;
    std::function<Functor_glBindBufferRange::glProcType>                             BindBufferRange;
    std::function<Functor_glBindBuffersBase::glProcType>                             BindBuffersBase;
    std::function<Functor_glBindBuffersRange::glProcType>                            BindBuffersRange;
    std::function<Functor_glBindFragDataLocation::glProcType>                        BindFragDataLocation;
    std::function<Functor_glBindFragDataLocationIndexed::glProcType>                 BindFragDataLocationIndexed;
    std::function<Functor_glBindFramebuffer::glProcType>                             BindFramebuffer;
    std::function<Functor_glBindImageTexture::glProcType>                            BindImageTexture;
    std::function<Functor_glBindImageTextures::glProcType>                           BindImageTextures;
    std::function<Functor_glBindProgramPipeline::glProcType>                         BindProgramPipeline;
    std::function<Functor_glBindRenderbuffer::glProcType>                            BindRenderbuffer;
    std::function<Functor_glBindSampler::glProcType>                                 BindSampler;
    std::function<Functor_glBindSamplers::glProcType>                                BindSamplers;
    std::function<Functor_glBindTexture::glProcType>                                 BindTexture;
    std::function<Functor_glBindTextures::glProcType>                                BindTextures;
    std::function<Functor_glBindTransformFeedback::glProcType>                       BindTransformFeedback;
    std::function<Functor_glBindVertexArray::glProcType>                             BindVertexArray;
    std::function<Functor_glBindVertexBuffer::glProcType>                            BindVertexBuffer;
    std::function<Functor_glBlendColor::glProcType>                                  BlendColor;
    std::function<Functor_glBlendEquation::glProcType>                               BlendEquation;
    std::function<Functor_glBlendEquationSeparate::glProcType>                       BlendEquationSeparate;
    std::function<Functor_glBlendFunc::glProcType>                                   BlendFunc;
    std::function<Functor_glBlendFuncSeparate::glProcType>                           BlendFuncSeparate;
    std::function<Functor_glBlendFuncSeparatei::glProcType>                          BlendFuncSeparatei;
    std::function<Functor_glBlitFramebuffer::glProcType>                             BlitFramebuffer;
    std::function<Functor_glBufferData::glProcType>                                  BufferData;
    std::function<Functor_glBufferStorage::glProcType>                               BufferStorage;
    std::function<Functor_glBufferSubData::glProcType>                               BufferSubData;
    std::function<Functor_glCheckFramebufferStatus::glProcType>                      CheckFramebufferStatus;
    std::function<Functor_glClampColor::glProcType>                                  ClampColor;
    std::function<Functor_glClear::glProcType>                                       Clear;
    std::function<Functor_glClearBuffer::glProcType>                                 ClearBuffer;
    std::function<Functor_glClearBufferData::glProcType>                             ClearBufferData;
    std::function<Functor_glClearBufferSubData::glProcType>                          ClearBufferSubData;
    std::function<Functor_glClearColor::glProcType>                                  ClearColor;
    std::function<Functor_glClearDepth::glProcType>                                  ClearDepth;
    std::function<Functor_glClearStencil::glProcType>                                ClearStencil;
    std::function<Functor_glClearTexImage::glProcType>                               ClearTexImage;
    std::function<Functor_glClearTexSubImage::glProcType>                            ClearTexSubImage;
    std::function<Functor_glClientWaitSync::glProcType>                              ClientWaitSync;
    std::function<Functor_glColorMask::glProcType>                                   ColorMask;
    std::function<Functor_glCompileShader::glProcType>                               CompileShader;
    std::function<Functor_glCompressedTexImage1D::glProcType>                        CompressedTexImage1D;
    std::function<Functor_glCompressedTexImage2D::glProcType>                        CompressedTexImage2D;
    std::function<Functor_glCompressedTexImage3D::glProcType>                        CompressedTexImage3D;
    std::function<Functor_glCompressedTexSubImage1D::glProcType>                     CompressedTexSubImage1D;
    std::function<Functor_glCompressedTexSubImage2D::glProcType>                     CompressedTexSubImage2D;
    std::function<Functor_glCompressedTexSubImage3D::glProcType>                     CompressedTexSubImage3D;
    std::function<Functor_glCopyBufferSubData::glProcType>                           CopyBufferSubData;
    std::function<Functor_glCopyImageSubData::glProcType>                            CopyImageSubData;
    std::function<Functor_glCopyTexImage1D::glProcType>                              CopyTexImage1D;
    std::function<Functor_glCopyTexImage2D::glProcType>                              CopyTexImage2D;
    std::function<Functor_glCopyTexSubImage1D::glProcType>                           CopyTexSubImage1D;
    std::function<Functor_glCopyTexSubImage2D::glProcType>                           CopyTexSubImage2D;
    std::function<Functor_glCopyTexSubImage3D::glProcType>                           CopyTexSubImage3D;
    std::function<Functor_glBindVertexBuffers::glProcType>                           BindVertexBuffers;
    std::function<Functor_glCreateProgram::glProcType>                               CreateProgram;
    std::function<Functor_glCreateShader::glProcType>                                CreateShader;
    std::function<Functor_glCreateShaderProgram::glProcType>                         CreateShaderProgram;
    std::function<Functor_glCreateShaderProgramv::glProcType>                        CreateShaderProgramv;
    std::function<Functor_glCullFace::glProcType>                                    CullFace;
    std::function<Functor_glDebugMessageCallback::glProcType>                        DebugMessageCallback;
    std::function<Functor_glDebugMessageControl::glProcType>                         DebugMessageControl;
    std::function<Functor_glDebugMessageInsert::glProcType>                          DebugMessageInsert;
    std::function<Functor_glDeleteBuffers::glProcType>                               DeleteBuffers;
    std::function<Functor_glDeleteFramebuffers::glProcType>                          DeleteFramebuffers;
    std::function<Functor_glDeleteProgram::glProcType>                               DeleteProgram;
    std::function<Functor_glDeleteProgramPipelines::glProcType>                      DeleteProgramPipelines;
    std::function<Functor_glDeleteQueries::glProcType>                               DeleteQueries;
    std::function<Functor_glDeleteRenderbuffers::glProcType>                         DeleteRenderbuffers;
    std::function<Functor_glDeleteSamplers::glProcType>                              DeleteSamplers;
    std::function<Functor_glDeleteShader::glProcType>                                DeleteShader;
    std::function<Functor_glDeleteSync::glProcType>                                  DeleteSync;
    std::function<Functor_glDeleteTextures::glProcType>                              DeleteTextures;
    std::function<Functor_glDeleteTransformFeedbacks::glProcType>                    DeleteTransformFeedbacks;
    std::function<Functor_glDeleteVertexArrays::glProcType>                          DeleteVertexArrays;
    std::function<Functor_glDepthFunc::glProcType>                                   DepthFunc;
    std::function<Functor_glDepthMask::glProcType>                                   DepthMask;
    std::function<Functor_glDepthRange::glProcType>                                  DepthRange;
    std::function<Functor_glDepthRangeArray::glProcType>                             DepthRangeArray;
    std::function<Functor_glDepthRangeIndexed::glProcType>                           DepthRangeIndexed;
    std::function<Functor_glDetachShader::glProcType>                                DetachShader;
    std::function<Functor_glDisable::glProcType>                                     Disable;
    std::function<Functor_glDisablei::glProcType>                                    Disablei;
    std::function<Functor_glDisableVertexAttribArray::glProcType>                    DisableVertexAttribArray;
    std::function<Functor_glDispatchCompute::glProcType>                             DispatchCompute;
    std::function<Functor_glDispatchComputeIndirect::glProcType>                     DispatchComputeIndirect;
    std::function<Functor_glDrawArrays::glProcType>                                  DrawArrays;
    std::function<Functor_glDrawArraysIndirect::glProcType>                          DrawArraysIndirect;
    std::function<Functor_glDrawArraysInstanced::glProcType>                         DrawArraysInstanced;
    std::function<Functor_glDrawArraysInstancedBaseInstance::glProcType>             DrawArraysInstancedBaseInstance;
    std::function<Functor_glDrawBuffer::glProcType>                                  DrawBuffer;
    std::function<Functor_glDrawBuffers::glProcType>                                 DrawBuffers;
    std::function<Functor_glDrawElements::glProcType>                                DrawElements;
    std::function<Functor_glDrawElementsBaseVertex::glProcType>                      DrawElementsBaseVertex;
    std::function<Functor_glDrawElementsIndirect::glProcType>                        DrawElementsIndirect;
    std::function<Functor_glDrawElementsInstanced::glProcType>                       DrawElementsInstanced;
    std::function<Functor_glDrawElementsInstancedBaseInstance::glProcType>           DrawElementsInstancedBaseInstance;
    std::function<Functor_glDrawElementsInstancedBaseVertex::glProcType>             DrawElementsInstancedBaseVertex;
    std::function<Functor_glDrawElementsInstancedBaseVertexBaseInstance::glProcType> DrawElementsInstancedBaseVertexBaseInstance;
    std::function<Functor_glDrawRangeElements::glProcType>                           DrawRangeElements;
    std::function<Functor_glDrawRangeElementsBaseVertex::glProcType>                 DrawRangeElementsBaseVertex;
    std::function<Functor_glDrawTransformFeedback::glProcType>                       DrawTransformFeedback;
    std::function<Functor_glDrawTransformFeedbackInstanced::glProcType>              DrawTransformFeedbackInstanced;
    std::function<Functor_glDrawTransformFeedbackStream::glProcType>                 DrawTransformFeedbackStream;
    std::function<Functor_glDrawTransformFeedbackStreamInstanced::glProcType>        DrawTransformFeedbackStreamInstanced;
    std::function<Functor_glEnable::glProcType>                                      Enable;
    std::function<Functor_glEnablei::glProcType>                                     Enablei;
    std::function<Functor_glEnableVertexAttribArray::glProcType>                     EnableVertexAttribArray;
    std::function<Functor_glEndConditionalRender::glProcType>                        EndConditionalRender;
    std::function<Functor_glEndQuery::glProcType>                                    EndQuery;
    std::function<Functor_glEndQueryIndexed::glProcType>                             EndQueryIndexed;
    std::function<Functor_glEndTransformFeedback::glProcType>                        EndTransformFeedback;
    std::function<Functor_glFenceSync::glProcType>                                   FenceSync;
    std::function<Functor_glFinish::glProcType>                                      Finish;
    std::function<Functor_glFlush::glProcType>                                       Flush;
    std::function<Functor_glFlushMappedBufferRange::glProcType>                      FlushMappedBufferRange;
    std::function<Functor_glFramebufferParameter::glProcType>                        FramebufferParameter;
    std::function<Functor_glFramebufferParameteri::glProcType>                       FramebufferParameteri;
    std::function<Functor_glFramebufferRenderbuffer::glProcType>                     FramebufferRenderbuffer;
    std::function<Functor_glFramebufferTexture::glProcType>                          FramebufferTexture;
    std::function<Functor_glFramebufferTexture1D::glProcType>                        FramebufferTexture1D;
    std::function<Functor_glFramebufferTexture2D::glProcType>                        FramebufferTexture2D;
    std::function<Functor_glFramebufferTexture3D::glProcType>                        FramebufferTexture3D;
    std::function<Functor_glFramebufferTextureLayer::glProcType>                     FramebufferTextureLayer;
    std::function<Functor_glFrontFace::glProcType>                                   FrontFace;
    std::function<Functor_glGenBuffers::glProcType>                                  GenBuffers;
    std::function<Functor_glGenerateMipmap::glProcType>                              GenerateMipmap;
    std::function<Functor_glGenFramebuffers::glProcType>                             GenFramebuffers;
    std::function<Functor_glGenProgramPipelines::glProcType>                         GenProgramPipelines;
    std::function<Functor_glGenQueries::glProcType>                                  GenQueries;
    std::function<Functor_glGenRenderbuffers::glProcType>                            GenRenderbuffers;
    std::function<Functor_glGenSamplers::glProcType>                                 GenSamplers;
    std::function<Functor_glGenTextures::glProcType>                                 GenTextures;
    std::function<Functor_glGenTransformFeedbacks::glProcType>                       GenTransformFeedbacks;
    std::function<Functor_glGenVertexArrays::glProcType>                             GenVertexArrays;
    std::function<Functor_glGet::glProcType>                                         Get;
    std::function<Functor_glGetBooleanv::glProcType>                                 GetBooleanv;
    std::function<Functor_glGetDoublev::glProcType>                                  GetDoublev;
    std::function<Functor_glGetFloatv::glProcType>                                   GetFloatv;
    std::function<Functor_glGetInteger64v::glProcType>                               GetInteger64v;
    std::function<Functor_glGetIntegerv::glProcType>                                 GetIntegerv;
    std::function<Functor_glGetActiveAtomicCounterBuffer::glProcType>                GetActiveAtomicCounterBuffer;
    std::function<Functor_glGetActiveAtomicCounterBufferiv::glProcType>              GetActiveAtomicCounterBufferiv;
    std::function<Functor_glGetActiveAttrib::glProcType>                             GetActiveAttrib;
    std::function<Functor_glGetActiveSubroutineName::glProcType>                     GetActiveSubroutineName;
    std::function<Functor_glGetActiveSubroutineUniform::glProcType>                  GetActiveSubroutineUniform;
    std::function<Functor_glGetActiveSubroutineUniformName::glProcType>              GetActiveSubroutineUniformName;
    std::function<Functor_glGetActiveUniform::glProcType>                            GetActiveUniform;
    std::function<Functor_glGetActiveUniformBlock::glProcType>                       GetActiveUniformBlock;
    std::function<Functor_glGetActiveUniformBlockName::glProcType>                   GetActiveUniformBlockName;
    std::function<Functor_glGetActiveUniformName::glProcType>                        GetActiveUniformName;
    std::function<Functor_glGetActiveUniforms::glProcType>                           GetActiveUniforms;
    std::function<Functor_glGetActiveUniformsiv::glProcType>                         GetActiveUniformsiv;
    std::function<Functor_glGetAttachedShaders::glProcType>                          GetAttachedShaders;
    std::function<Functor_glGetAttribLocation::glProcType>                           GetAttribLocation;
    std::function<Functor_glGetBufferParameter::glProcType>                          GetBufferParameter;
    std::function<Functor_glGetBufferPointer::glProcType>                            GetBufferPointer;
    std::function<Functor_glGetBufferSubData::glProcType>                            GetBufferSubData;
    std::function<Functor_glGetCompressedTexImage::glProcType>                       GetCompressedTexImage;
    std::function<Functor_glGetDebugMessageLog::glProcType>                          GetDebugMessageLog;
    std::function<Functor_glGetError::glProcType>                                    GetError;
    std::function<Functor_glGetFragDataIndex::glProcType>                            GetFragDataIndex;
    std::function<Functor_glGetFragDataLocation::glProcType>                         GetFragDataLocation;
    std::function<Functor_glGetFramebufferAttachmentParameter::glProcType>           GetFramebufferAttachmentParameter;
    std::function<Functor_glGetFramebufferParameter::glProcType>                     GetFramebufferParameter;
    std::function<Functor_glGetFramebufferParameteriv::glProcType>                   GetFramebufferParameteriv;
    std::function<Functor_glGetInternalformat::glProcType>                           GetInternalformat;
    std::function<Functor_glGetMultisample::glProcType>                              GetMultisample;
    std::function<Functor_glGetObjectLabel::glProcType>                              GetObjectLabel;
    std::function<Functor_glGetObjectPtrLabel::glProcType>                           GetObjectPtrLabel;
    std::function<Functor_glGetProgram::glProcType>                                  GetProgram;
    std::function<Functor_glGetProgramBinary::glProcType>                            GetProgramBinary;
    std::function<Functor_glGetProgramInfoLog::glProcType>                           GetProgramInfoLog;
    std::function<Functor_glGetProgramInterface::glProcType>                         GetProgramInterface;
    std::function<Functor_glGetProgramPipeline::glProcType>                          GetProgramPipeline;
    std::function<Functor_glGetProgramPipelineInfoLog::glProcType>                   GetProgramPipelineInfoLog;
    std::function<Functor_glGetProgramResource::glProcType>                          GetProgramResource;
    std::function<Functor_glGetProgramResourceLocation::glProcType>                  GetProgramResourceLocation;
    std::function<Functor_glGetProgramResourceLocationIndex::glProcType>             GetProgramResourceLocationIndex;
    std::function<Functor_glGetProgramResourceIndex::glProcType>                     GetProgramResourceIndex;
    std::function<Functor_glGetProgramResourceName::glProcType>                      GetProgramResourceName;
    std::function<Functor_glGetProgramStage::glProcType>                             GetProgramStage;
    std::function<Functor_glGetQuery::glProcType>                                    GetQuery;
    std::function<Functor_glGetQueryIndexed::glProcType>                             GetQueryIndexed;
    std::function<Functor_glGetQueryObject::glProcType>                              GetQueryObject;
    std::function<Functor_glGetRenderbufferParameter::glProcType>                    GetRenderbufferParameter;
    std::function<Functor_glGetSamplerParameter::glProcType>                         GetSamplerParameter;
    std::function<Functor_glGetShader::glProcType>                                   GetShader;
    std::function<Functor_glGetShaderInfoLog::glProcType>                            GetShaderInfoLog;
    std::function<Functor_glGetShaderPrecisionFormat::glProcType>                    GetShaderPrecisionFormat;
    std::function<Functor_glGetShaderSource::glProcType>                             GetShaderSource;
    std::function<Functor_glGetString::glProcType>                                   GetString;
    std::function<Functor_glGetStringi::glProcType>                                  GetStringi;
    std::function<Functor_glGetSubroutineIndex::glProcType>                          GetSubroutineIndex;
    std::function<Functor_glGetSubroutineUniformLocation::glProcType>                GetSubroutineUniformLocation;
    std::function<Functor_glGetSync::glProcType>                                     GetSync;
    std::function<Functor_glGetTexImage::glProcType>                                 GetTexImage;
    std::function<Functor_glGetTexLevelParameter::glProcType>                        GetTexLevelParameter;
    std::function<Functor_glGetTexParameter::glProcType>                             GetTexParameter;
    std::function<Functor_glGetTransformFeedbackVarying::glProcType>                 GetTransformFeedbackVarying;
    std::function<Functor_glGetUniform::glProcType>                                  GetUniform;
    std::function<Functor_glGetUniformBlockIndex::glProcType>                        GetUniformBlockIndex;
    std::function<Functor_glGetUniformIndices::glProcType>                           GetUniformIndices;
    std::function<Functor_glGetUniformLocation::glProcType>                          GetUniformLocation;
    std::function<Functor_glGetUniformSubroutine::glProcType>                        GetUniformSubroutine;
    std::function<Functor_glGetVertexAttrib::glProcType>                             GetVertexAttrib;
    std::function<Functor_glGetVertexAttribPointer::glProcType>                      GetVertexAttribPointer;
    std::function<Functor_glHint::glProcType>                                        Hint;
    std::function<Functor_glInvalidateBufferData::glProcType>                        InvalidateBufferData;
    std::function<Functor_glInvalidateBufferSubData::glProcType>                     InvalidateBufferSubData;
    std::function<Functor_glInvalidateFramebuffer::glProcType>                       InvalidateFramebuffer;
    std::function<Functor_glInvalidateSubFramebuffer::glProcType>                    InvalidateSubFramebuffer;
    std::function<Functor_glInvalidateTexImage::glProcType>                          InvalidateTexImage;
    std::function<Functor_glInvalidateTexSubImage::glProcType>                       InvalidateTexSubImage;
    std::function<Functor_glIsBuffer::glProcType>                                    IsBuffer;
    std::function<Functor_glIsEnabled::glProcType>                                   IsEnabled;
    std::function<Functor_glIsFramebuffer::glProcType>                               IsFramebuffer;
    std::function<Functor_glIsProgram::glProcType>                                   IsProgram;
    std::function<Functor_glIsProgramPipeline::glProcType>                           IsProgramPipeline;
    std::function<Functor_glIsQuery::glProcType>                                     IsQuery;
    std::function<Functor_glIsRenderbuffer::glProcType>                              IsRenderbuffer;
    std::function<Functor_glIsSampler::glProcType>                                   IsSampler;
    std::function<Functor_glIsShader::glProcType>                                    IsShader;
    std::function<Functor_glIsSync::glProcType>                                      IsSync;
    std::function<Functor_glIsTexture::glProcType>                                   IsTexture;
    std::function<Functor_glIsTransformFeedback::glProcType>                         IsTransformFeedback;
    std::function<Functor_glIsVertexArray::glProcType>                               IsVertexArray;
    std::function<Functor_glLineWidth::glProcType>                                   LineWidth;
    std::function<Functor_glLinkProgram::glProcType>                                 LinkProgram;
    std::function<Functor_glLogicOp::glProcType>                                     LogicOp;
    std::function<Functor_glMapBuffer::glProcType>                                   MapBuffer;
    std::function<Functor_glMapBufferRange::glProcType>                              MapBufferRange;
    std::function<Functor_glMemoryBarrier::glProcType>                               MemoryBarrier;
    std::function<Functor_glMinSampleShading::glProcType>                            MinSampleShading;
    std::function<Functor_glMultiDrawArrays::glProcType>                             MultiDrawArrays;
    std::function<Functor_glMultiDrawArraysIndirect::glProcType>                     MultiDrawArraysIndirect;
    std::function<Functor_glMultiDrawElements::glProcType>                           MultiDrawElements;
    std::function<Functor_glMultiDrawElementsBaseVertex::glProcType>                 MultiDrawElementsBaseVertex;
    std::function<Functor_glMultiDrawElementsIndirect::glProcType>                   MultiDrawElementsIndirect;
    std::function<Functor_glObjectLabel::glProcType>                                 ObjectLabel;
    std::function<Functor_glObjectPtrLabel::glProcType>                              ObjectPtrLabel;
    std::function<Functor_glPatchParameter::glProcType>                              PatchParameter;
    std::function<Functor_glPauseTransformFeedback::glProcType>                      PauseTransformFeedback;
    std::function<Functor_glPixelStore::glProcType>                                  PixelStore;
    std::function<Functor_glPointParameter::glProcType>                              PointParameter;
    std::function<Functor_glPointSize::glProcType>                                   PointSize;
    std::function<Functor_glPolygonMode::glProcType>                                 PolygonMode;
    std::function<Functor_glPolygonOffset::glProcType>                               PolygonOffset;
    std::function<Functor_glPopDebugGroup::glProcType>                               PopDebugGroup;
    std::function<Functor_glPrimitiveRestartIndex::glProcType>                       PrimitiveRestartIndex;
    std::function<Functor_glProgramBinary::glProcType>                               ProgramBinary;
    std::function<Functor_glProgramParameter::glProcType>                            ProgramParameter;
    std::function<Functor_glProgramUniform::glProcType>                              ProgramUniform;
    std::function<Functor_glProgramUniformMatrix::glProcType>                        ProgramUniformMatrix;
    std::function<Functor_glProvokingVertex::glProcType>                             ProvokingVertex;
    std::function<Functor_glPushDebugGroup::glProcType>                              PushDebugGroup;
    std::function<Functor_glQueryCounter::glProcType>                                QueryCounter;
    std::function<Functor_glReadBuffer::glProcType>                                  ReadBuffer;
    std::function<Functor_glReadPixels::glProcType>                                  ReadPixels;
    std::function<Functor_glReleaseShaderCompiler::glProcType>                       ReleaseShaderCompiler;
    std::function<Functor_glRenderbufferStorage::glProcType>                         RenderbufferStorage;
    std::function<Functor_glRenderbufferStorageMultisample::glProcType>              RenderbufferStorageMultisample;
    std::function<Functor_glResumeTransformFeedback::glProcType>                     ResumeTransformFeedback;
    std::function<Functor_glSampleCoverage::glProcType>                              SampleCoverage;
    std::function<Functor_glSampleMask::glProcType>                                  SampleMask;
    std::function<Functor_glSamplerParameter::glProcType>                            SamplerParameter;
    std::function<Functor_glScissor::glProcType>                                     Scissor;
    std::function<Functor_glScissorArray::glProcType>                                ScissorArray;
    std::function<Functor_glScissorIndexed::glProcType>                              ScissorIndexed;
    std::function<Functor_glShaderBinary::glProcType>                                ShaderBinary;
    std::function<Functor_glShaderSource::glProcType>                                ShaderSource;
    std::function<Functor_glShaderStorageBlockBinding::glProcType>                   ShaderStorageBlockBinding;
    std::function<Functor_glStencilFunc::glProcType>                                 StencilFunc;
    std::function<Functor_glStencilFuncSeparate::glProcType>                         StencilFuncSeparate;
    std::function<Functor_glStencilMask::glProcType>                                 StencilMask;
    std::function<Functor_glStencilMaskSeparate::glProcType>                         StencilMaskSeparate;
    std::function<Functor_glStencilOp::glProcType>                                   StencilOp;
    std::function<Functor_glStencilOpSeparate::glProcType>                           StencilOpSeparate;
    std::function<Functor_glTexBuffer::glProcType>                                   TexBuffer;
    std::function<Functor_glTexBufferRange::glProcType>                              TexBufferRange;
    std::function<Functor_glTexImage1D::glProcType>                                  TexImage1D;
    std::function<Functor_glTexImage2D::glProcType>                                  TexImage2D;
    std::function<Functor_glTexImage2DMultisample::glProcType>                       TexImage2DMultisample;
    std::function<Functor_glTexImage3D::glProcType>                                  TexImage3D;
    std::function<Functor_glTexImage3DMultisample::glProcType>                       TexImage3DMultisample;
    std::function<Functor_glTexParameter::glProcType>                                TexParameter;
    std::function<Functor_glTexStorage1D::glProcType>                                TexStorage1D;
    std::function<Functor_glTexStorage2D::glProcType>                                TexStorage2D;
    std::function<Functor_glTexStorage2DMultisample::glProcType>                     TexStorage2DMultisample;
    std::function<Functor_glTexStorage3D::glProcType>                                TexStorage3D;
    std::function<Functor_glTexStorage3DMultisample::glProcType>                     TexStorage3DMultisample;
    std::function<Functor_glTexSubImage1D::glProcType>                               TexSubImage1D;
    std::function<Functor_glTexSubImage2D::glProcType>                               TexSubImage2D;
    std::function<Functor_glTexSubImage3D::glProcType>                               TexSubImage3D;
    std::function<Functor_glTextureView::glProcType>                                 TextureView;
    std::function<Functor_glTransformFeedbackVaryings::glProcType>                   TransformFeedbackVaryings;
    std::function<Functor_glUniform::glProcType>                                     Uniform;
    std::function<Functor_glUniformBlockBinding::glProcType>                         UniformBlockBinding;
    std::function<Functor_glUniformMatrix::glProcType>                               UniformMatrix;
    std::function<Functor_glUniformSubroutines::glProcType>                          UniformSubroutines;
    std::function<Functor_glUnmapBuffer::glProcType>                                 UnmapBuffer;
    std::function<Functor_glUseProgram::glProcType>                                  UseProgram;
    std::function<Functor_glUseProgramStages::glProcType>                            UseProgramStages;
    std::function<Functor_glValidateProgram::glProcType>                             ValidateProgram;
    std::function<Functor_glValidateProgramPipeline::glProcType>                     ValidateProgramPipeline;
    std::function<Functor_glVertexAttrib::glProcType>                                VertexAttrib;
    std::function<Functor_glVertexAttribBinding::glProcType>                         VertexAttribBinding;
    std::function<Functor_glVertexAttribDivisor::glProcType>                         VertexAttribDivisor;
    std::function<Functor_glVertexAttribFormat::glProcType>                          VertexAttribFormat;
    std::function<Functor_glVertexAttribIFormat::glProcType>                         VertexAttribIFormat;
    std::function<Functor_glVertexAttribIPointer::glProcType>                        VertexAttribIPointer;
    std::function<Functor_glVertexAttribLFormat::glProcType>                         VertexAttribLFormat;
    std::function<Functor_glVertexAttribLPointer::glProcType>                        VertexAttribLPointer;
    std::function<Functor_glVertexAttribPointer::glProcType>                         VertexAttribPointer;
    std::function<Functor_glVertexBindingDivisor::glProcType>                        VertexBindingDivisor;
    std::function<Functor_glViewport::glProcType>                                    Viewport;
    std::function<Functor_glViewportArray::glProcType>                               ViewportArray;
    std::function<Functor_glViewportIndexed::glProcType>                             ViewportIndexed;
    std::function<Functor_glWaitSync::glProcType>                                    WaitSync;

  private:

    glfw::wrap::Window *context_;
};

void
print_platform_info()
{
    using namespace glfw::wrap;

    const std::unordered_map<Platform, std::string_view> platform_name {
            std::make_pair(Platform::Undefined, "Undefined"),
            std::make_pair(Platform::Win32, "Win32"),
            std::make_pair(Platform::Cocoa, "Cocoa"),
            std::make_pair(Platform::Wayland, "Wayland"),
            std::make_pair(Platform::X11, "X11")
    };

    std::cout << "glfw.platform: " << platform_name.at(get_platform()) << std::endl;
}

void
print_monitors_info()
{
    using namespace glfw::wrap;

    auto primary = get_primary_monitor();
    std::cout << "monitors:" << std::endl;

    for (auto m : get_monitors())
    {
        for (auto vm : get_video_modes(m))
        {
            std::cout << "{" << std::endl;
            std::cout << "\tname: " << get_monitor_name(m) << std::endl;
            {
                auto [x, y] = get_monitor_pos(m);
                std::cout << "\tpos: " << x << ", " << y << std::endl;
            }
            {
                auto [x, y] = get_monitor_content_scale(m);
                std::cout << "\tscale: " << x << ", " << y << std::endl;
            }
            {
                auto [w, h] = get_monitor_physical_size(m);
                std::cout << "\tsize: " << w << ", " << h << std::endl;
            }
            {
                auto [pos, size] = get_monitor_workarea(m);
                std::cout << "\tworkarea: " << pos.x << ", " << pos.y << ", " << size.width << ", " << size.height << std::endl;
            }

            std::cout << "\theight: " << vm.height << std::endl;
            std::cout << "\twidth: " << vm.width << std::endl;
            std::cout << "\trefreshRate: " << vm.refreshRate << std::endl;
            std::cout << "\tredBits: " << vm.redBits << std::endl;
            std::cout << "\tgreenBits: " << vm.greenBits << std::endl;
            std::cout << "\tblueBits: " << vm.blueBits << std::endl;
            std::cout << "}" << std::endl;
        }
    }
}

void
print_gl_info()
{
    using namespace glfw::wrap;

    std::cout << "opengl.vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "opengl.renderer: " << glGetString(GL_RENDERER) << std::endl;
    {
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        std::cout << "opengl.version: " << major << "." << minor << std::endl;
    }
    std::cout << "opengl.version_info: " << glGetString(GL_VERSION) << std::endl;
    {
        GLint profile;
        glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
        bool is_profile_core   = (profile & GL_CONTEXT_CORE_PROFILE_BIT) == GL_CONTEXT_CORE_PROFILE_BIT;
        bool is_profile_compat = (profile & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT) == GL_CONTEXT_COMPATIBILITY_PROFILE_BIT;
        std::cout << "opengl.profile: " << ((is_profile_core) ? "core" : "compatibility") << std::endl;
    }
    {
        GLint context;
        glGetIntegerv(GL_CONTEXT_FLAGS, &context);
        bool is_compat   = (context & GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT) == GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT;
        bool is_debug    = (context & GL_CONTEXT_FLAG_DEBUG_BIT) == GL_CONTEXT_FLAG_DEBUG_BIT;
        bool is_robust   = (context & GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT) == GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT;
        bool is_no_error = (context & GL_CONTEXT_FLAG_NO_ERROR_BIT) == GL_CONTEXT_FLAG_NO_ERROR_BIT;

        std::cout << "opengl.context.is_compat: " << std::boolalpha << is_compat << std::endl;
        std::cout << "opengl.context.is_debug: " << std::boolalpha << is_debug << std::endl;
        std::cout << "opengl.context.is_robust: " << std::boolalpha << is_robust << std::endl;
        std::cout << "opengl.context.is_no_error: " << std::boolalpha << is_no_error << std::endl;
    }
    {
        GLint shader_lang_versions = 0;
        glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &shader_lang_versions);
        std::vector<std::string_view> shader_versions;
        shader_versions.resize(shader_lang_versions);
        GLint next_ver_id = 0;
        for (auto &ver : shader_versions)
        {
            ver = (char *)glGetStringi(GL_SHADING_LANGUAGE_VERSION, next_ver_id++);
        }
        if (shader_lang_versions)
        {
            auto version = std::accumulate(shader_versions.cbegin(), shader_versions.cend(), std::string {}, [](auto acc, const auto ver)
                                           {
                                               if (ver.empty())
                                               {
                                                   return std::move(acc);
                                               }
                                               else
                                               {
                                                   return std::move((acc.empty()) ? "\t" + std::string {ver} : acc + ",\n\t" + std::string {ver});
                                               }
                                           });

            std::cout << "opengl.glsl_version: [" << std::endl
                      << version << std::endl
                      << "]" << std::endl;
        }
    }
    std::cout << "opengl.shading_lang_version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "opengl.extensions: [" << std::endl;

    auto get_context_ext = []() -> std::set<std::string>
    {
        std::set<std::string> ext_names;

        GLint ext_num = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &ext_num);
        for (size_t i = 0; i < ext_num; ++i)
        {
            ext_names.insert({(char *)glGetStringi(GL_EXTENSIONS, i)});
        }

        return ext_names;
    };

    const auto extensions       = get_context_ext();
    auto       print_extensions = [](const auto &extensions)
    {
        auto ext_string = std::accumulate(extensions.cbegin(), extensions.cend(), std::string {}, [](auto acc, const auto &elem)
                                          {
                                              return std::move((acc.empty()) ? ("\t" + elem) : (acc + ",\n\t" + elem));
                                          });
        std::cout << ext_string << std::endl;
    };

    print_extensions(extensions);
    std::cout << "]" << std::endl;
    std::cout << "\topengl.extensions_count: " << extensions.size() << std::endl;
}

int
main(
        int   argc,
        char *argv[]
)
{
    using namespace glfw::wrap;

    std::srand((unsigned)time(NULL));

    auto apply_init_hints = [](const auto &hints)
    {
        std::for_each(
                hints.begin(),
                hints.end(),
                [](const auto hint)
                {
                    glfw::wrap::init_hint(hint);
                }
        );
    };

    auto apply_window_hints = [](const auto &hints)
    {
        std::for_each(
                hints.begin(),
                hints.end(),
                [](const auto hint)
                {
                    glfw::wrap::window_hint(hint);
                }
        );
    };

    auto print_context_gl_info = [](Window *window)
    {
        make_context_current(window);
        print_platform_info();
        print_monitors_info();
        print_gl_info();
        request_window_attention(window);
    };

    auto configure_gl_context = [&](Window *window) -> glLoadContext
    {
        make_context_current(window);
        swap_interval(1);

        gladLoadGLLoader((GLADloadproc)glfw::wrap::get_proc_address);

        auto gl = glLoadContext(window);

        print_context_gl_info(window);

        auto rand_float = []()
        {
            return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        };

        gl.ClearColor(rand_float(), rand_float(), rand_float(), 1.0);
        return gl;
    };

    auto configure_gl_contexts = [&](const auto &contexts) -> std::map<Window *, glLoadContext>
    {
        std::map<Window *, glLoadContext> result;

        std::for_each(contexts.cbegin(), contexts.cend(), [&](const auto ctx)
                      {
                          result.insert(std::make_pair(ctx, configure_gl_context(ctx)));
                      });
        return result;
    };

    const std::vector<Init_Hint> init_hints_gles_3_0 {
            {hint::init::AnglePlatformType {AnglePlatformType::OpenGl}}
    };

    const std::vector<Window_Hint> window_hints_gles_3_0 {
            {hint::window::ClientApi {ClientApi::OpenGles}},
            {hint::window::ContextCreationApi {ContextCreationApi::Native}},
            {hint::window::ContextVersionMajor {3}},
            {hint::window::ContextVersionMinor {0}},
#ifdef __APPLE__
            {hint::window::OpenGlForwardCompat {true}}, // for MacOS only
#endif
            {hint::window::OpenGlProfile {OpenGlProfile::Core}},
            {hint::window::DoubleBuffer {true}},
            {hint::window::ContextNoError {false}},
            {hint::window::ContextRobustness {ContextRobustness::LoseContextOnReset}},
            {hint::window::ContextDebug {true}},

            {hint::window::Resizable {false}},
            {hint::window::ScaleToMonitor {true}},
            {hint::window::ScaleFrameBuffer {true}},
            {hint::window::RefreshRate {}}
    };

    const std::vector<Window_Hint> window_hints_gl_4_6 {
            {hint::window::ClientApi {ClientApi::OpenGl}},
            {hint::window::ContextCreationApi {ContextCreationApi::Native}},
            {hint::window::ContextVersionMajor {4}},
            {hint::window::ContextVersionMinor {6}},
#ifdef __APPLE__
            {hint::window::OpenGlForwardCompat {true}}, // for MacOS only
#endif
            {hint::window::OpenGlProfile {OpenGlProfile::Core}},
            {hint::window::DoubleBuffer {true}},
            {hint::window::ContextNoError {false}},
            {hint::window::ContextRobustness {ContextRobustness::LoseContextOnReset}},
            {hint::window::ContextDebug {true}},

            {hint::window::Resizable {false}},
            {hint::window::ScaleToMonitor {true}},
            {hint::window::ScaleFrameBuffer {true}},
            {hint::window::RefreshRate {}}
    };

    apply_init_hints(init_hints_gles_3_0);
    auto res = init();

    std::set<Window *> windows;

    apply_window_hints(window_hints_gles_3_0);
    auto window = create_window(640, 640, "Wrapped GLFW GLES 3.0", nullptr, nullptr);
    windows.insert(window);

    default_window_hints();

    apply_window_hints(window_hints_gl_4_6);
    window = create_window(640, 640, "Wrapped GLFW GL 4.6", nullptr, nullptr);
    windows.insert(window);

    auto gl_contexts = configure_gl_contexts(windows);

    while (!windows.empty())
    {
        std::set<Window *> windows_to_close;
        for (auto window : windows)
        {
            if (!window_should_close(window))
            {
                poll_events();

                auto &gl = gl_contexts.at(window);
                gl.make_current();
                gl.Clear(GL_COLOR_BUFFER_BIT);

                swap_buffers(window);
            }
            else
            {
                windows_to_close.insert(window);
            }
        }
        for (auto window : windows_to_close)
        {
            windows.erase(window);
            destroy_window(window);
        }
    }

    ::glfw::wrap::terminate();

    return EXIT_SUCCESS;
}
