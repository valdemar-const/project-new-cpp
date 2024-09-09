#include <glmeta/glmeta.hpp>

using namespace glmeta;

int
main(int argc, const char *argv[])
{
    auto gl_load_proc = [](std::string_view) -> functions::GL_Any_Proc *
    {
        return reinterpret_cast<functions::GL_Any_Proc *>(nullptr);
    };
    GL_Load_Context<Client_Api::Gl, 1, 0, Profile::None, Load_Strategy::Immediate> {gl_load_proc};
    GL_Load_Context<Client_Api::Gl, 3, 3, Profile::Core, Load_Strategy::Immediate> {gl_load_proc};
    GL_Load_Context<Client_Api::Gles, 3, 0, Profile::Core, Load_Strategy::Immediate> {gl_load_proc};
    return 0;
}
