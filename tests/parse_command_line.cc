#include "symbols.hh"
#include "iod/parse_command_line.hh" 
#include "iod/json.hh"

int main()
{
  using namespace s;
  using namespace iod;

  // Simple options
  {
    const char* argv[] = {"", "--opt1" , "12", "--opt2", "abc"};
    auto opts = parse_command_line(5, argv,
                                   _opt1 = int(),
                                   _opt2 = std::string());

    assert(opts.opt1 == 12 and opts.opt2 == "abc");
    std::cout << json_encode(opts) << std::endl;
  }

  // Positionals
  {
    const char* argv[] = {"", "abc", "1.23", "--opt1" , "12"};
    auto opts = parse_command_line(5, argv,
                                   positionals(_opt2, _opt3),
                                   _opt1 = int(),
                                   _opt2 = std::string(),
                                   _opt3 = float());

    assert(opts.opt1 == 12 and opts.opt2 == "abc" and std::abs(opts.opt3 - 1.23) < 0.00001);
    std::cout << json_encode(opts) << std::endl;
  }

  // Defaults
  {
    const char* argv[] = {""};
    auto opts = parse_command_line(1, argv,
                                   _opt1 = int(3),
                                   _opt2 = std::string("abc"));

    assert(opts.opt1 == 3 and opts.opt2 == "abc");
    std::cout << json_encode(opts) << std::endl;
  }

  // Pointers
  {
    const char* argv[] = {"", "--opt1", "42"};
    int opt1 = 0;
    parse_command_line(3, argv,
                       _opt1 = &opt1);

    assert(opt1 == 42);
  }
  
  // Todo :

  // // flags
  // {
  //   const char* argv[] = {"", "--opt1", "0", "-abc"};
  //   auto opts = parse_command_line(5, argv,
  //                                  _opt1 = bool(),
  //                                  _a = bool(),
  //                                  _b = bool(),
  //                                  _c = bool());

  //   assert(opts.opt1 == true and
  //          opts.a == true and
  //          opts.b == true and
  //          opts.c == true);
  //   std::cout << json_encode(opts) << std::endl;
  // }

  // // equals option assignments
  // {
  //   const char* argv[] = {"", "--opt1=42"};
  //   auto opts = parse_command_line(5, argv,
  //                                  _opt1 = int());

  //   assert(opts.opt1 == 42);
  //   std::cout << json_encode(opts) << std::endl;
  // }
  

  // // short names
  // {
  //   const char* argv[] = {"", "-1" , "3", "-2", "abc"};
  //   auto opts = parse_command_line(1, argv,
  //                                  _opt1 | _1 = int(),
  //                                  _opt2 | _2 = std::string());

  //   assert(opts.opt1 == 3 and opts.opt2 == "abc");
  //   std::cout << json_encode(opts) << std::endl;
  // }

  // // required args
  // {
  //   const char* argv[] = {"", "-1" , "3", "-2", "abc"};
  //   auto opts = parse_command_line(1, argv,
  //                                  required(_opt1, _opt2),
  //                                  _opt1 | _1 = int(),
  //                                  _opt2 | _2 = std::string());

  //   assert(opts.opt1 == 3 and opts.opt2 == "abc");
  //   std::cout << json_encode(opts) << std::endl;
  // }

  // // Description.
  // {
  //   const char* argv[] = {"", "-1" , "3", "-2", "abc"};
  //   auto opts = parse_command_line(1, argv,
  //                                  description(
  //                                    _opt1 = "Set the first option of our test program."
  //                                    _opt2 = "Set the second option of our test program.")

  //                                    ),
  //                                  _opt1 | _1 = int(),
  //                                  _opt2 | _2 = std::string());

  //   assert(opts.opt1 == 3 and opts.opt2 == "abc");
  //   std::cout << json_encode(opts) << std::endl;
  // }
  
}
