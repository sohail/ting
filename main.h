//
//main.h
//Written by, Sohail Qayum Malik
//

#define	PARSE_ARGSX(a,x,y) a.parse(argc, const_cast<const char**>(argv), x, y)
#define PARSE_ARGS(x,y) if(args.parse(argc, const_cast<const char**>(argv),x,y) == 0)return 0

#define	INITIALIZE(a)	a.index=a.previousIndex=0
