#if (defined __linux__ || defined __unix__ || defined __CYGWIN__ || defined __APPLE__ || defined __MACH__ )

  // MISC ESCAPES
  #define RESET "\033[0m"
  #define CLEAR "\033[2J\033[;H"
  
  // BACKGROUND COLORS
  #define BBLACK   "\033[48;5;234m"
  #define BWHITE   "\033[48;5;238m"
  #define BYELLOW  "\033[48;5;136m"
  #define BORANGE  "\033[48;5;166m"
  #define BRED     "\033[48;5;124m"
  #define BMAGENTA "\033[48;5;125m"
  #define BVIOLET  "\033[48;5;61m"
  #define BBLUE    "\033[48;5;33m"
  #define BCYAN    "\033[48;5;37m"
  #define BGREEN   "\033[48;5;64m"


  // FOREGROUND COLORS
  #define FBLACK   "\033[38;5;234m"
  #define FWHITE   "\033[38;5;238m"
  #define FYELLOW  "\033[38;5;136m"
  #define FORANGE  "\033[38;5;166m"
  #define FRED     "\033[38;5;124m"
  #define FMAGENTA "\033[38;5;125m"
  #define FVIOLET  "\033[38;5;61m"
  #define FBLUE    "\033[38;5;33m"
  #define FCYAN    "\033[38;5;37m"
  #define FGREEN   "\033[38;5;64m"

#else

  // BACKGROUND COLORS
  #define BBLACK   ""
  #define BWHITE   ""
  #define BYELLOW  ""
  #define BORANGE  ""
  #define BRED     ""
  #define BMAGENTA ""
  #define BVIOLET  ""
  #define BBLUE    ""
  #define BCYAN    ""
  #define BGREEN   ""


  // FOREGROUND COLORS
  #define FBLACK   ""
  #define FWHITE   ""
  #define FYELLOW  ""
  #define FORANGE  ""
  #define FRED     ""
  #define FMAGENTA ""
  #define FVIOLET  ""
  #define FBLUE    ""
  #define FCYAN    ""
  #define FGREEN   ""

#endif       