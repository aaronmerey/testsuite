#include "ParseThat.h"
#include "util.h"
#include "dyninst_comp.h"
#include <sys/types.h>
#include <sys/stat.h>
using namespace Dyninst;

ParseThat::ParseThat() :
	pt_path("parseThat"),
	trans(T_None),
	suppress_ipc(false),
	nofork(false),
	verbosity(7),
	timeout_secs(300),
	do_trace(true),
	tracelength(0),
	print_summary_(true),
	parse_level(PL_Func),
	do_recursive(false),
	merge_tramps(false),
	inst_level_(IL_FuncEntry),
	include_libs_(false)
{
#if defined (os_windows_test)
	char slashc = '\\';
#else
	char slashc = '/';
#endif
	char slashbuf[3];
	sprintf(slashbuf, "%c", slashc);
	std::string slash(slashbuf);

	//  try to resolve the full path of the parseThat command
	//  first look in the user's PATH
	//  If not found, try looking in $DYNINST_ROOT/$PLATFORM/bin

	const char *path_var = getenv("PATH");
	if (path_var)
	{
		char *fullpath = searchPath(path_var, "parseThat");
		if (fullpath)
		{
			pt_path = std::string(fullpath);
			::free(fullpath);
			logerror("%s[%d]:  resolved parseThat to %s\n", FILE__, __LINE__, pt_path.c_str());
			return;
		}
	}

	//  If we get here, we didn't find it
	const char *dyn_root_env = getenv("DYNINST_ROOT");
	const char *plat_env = getenv("PLATFORM");

	if (!plat_env)
	{
#if defined (os_windows_test)
		plat_env = "i386-unknown-nt4.0";
#elif defined (os_linux_test)
#if defined (arch_x86_test)
		plat_env = "i386-unknown-linux2.4";
#elif defined (arch_ia64_test)
		plat_env = "ia64-unknown-linux2.4";
#elif defined (arch_x86_64_test)
		plat_env = "x86_64-unknown-linux2.4";
#elif defined (arch_power_test)
#if defined (arch_64bit_test)
		plat_env = "ppc64_linux";
#else
		plat_env = "ppc32_linux";
#endif
#endif
#elif defined (os_aix_test)
		plat_env = "rs6000-ibm-aix5.1";
#elif defined (os_solaris_test)
		//  annoyingly we don't seem to maintain an arch def that specifies
		//  solaris version through the build defines
		plat_env = "sparc-sun-solaris2.9";
#endif
	}

	if (dyn_root_env &&  plat_env)
	{
		std::string expect_pt_loc = std::string(dyn_root_env) + slash 
			+ std::string(plat_env) + slash + std::string("bin") 
			+ slash +std::string("parseThat");

		struct stat statbuf;
		if (!stat(expect_pt_loc.c_str(), &statbuf))
		{
			pt_path = expect_pt_loc;
			logerror("%s[%d]:  resolved parseThat to %s\n", FILE__, __LINE__, pt_path.c_str());
			return;
		}
		else
		{
			logerror("%s[%d]:  cannot resolve pt path '%s'\n", FILE__, __LINE__, 
					expect_pt_loc.c_str());
		}
	}
	else
	{
		logerror("%s[%d]:  DYNINST_ROOT %s, PLATFORM %s, can't resolve canonical parseThat loc\n",
				FILE__, __LINE__, dyn_root_env ? "set" : "not set", plat_env ? "set" : "not set");
	}

	//  try looking at relative paths
	//  (1) assume we are in $DYNINST_ROOT/dyninst/newtestsuite/$PLATFORM
	//  so look in ../../../$PLATFORM/bin

	if (plat_env)
	{
		char cwdbuf[1024];
		char *last_slash = NULL;
		const char * cwd = getcwd(cwdbuf, 1024);

		if (cwd)
			last_slash = strrchr(cwd, slashc);

		if (last_slash) 
		{
			*last_slash = '\0';
			last_slash = strrchr(cwd, slashc);
			if (last_slash) 
			{
				*last_slash = '\0';
				last_slash = strrchr(cwd, slashc);
				if (last_slash) 
				{
					*last_slash = '\0';
					std::string expected_pt_path = std::string(cwd) + slash 
						+ std::string(plat_env) + slash + std::string("bin") 
						+ slash + std::string("parseThat");

					struct stat statbuf;
					if (!stat(expected_pt_path.c_str(), &statbuf))
					{
						pt_path = expected_pt_path;
						logerror("%s[%d]:  resolved parseThat to %s\n", FILE__, __LINE__, pt_path.c_str());
						return;
					}

					logerror("%s[%d]: could not find parseThat at loc: '%s'\n", 
							FILE__, __LINE__, expected_pt_path.c_str());
				}
			}
		}

	}
}

ParseThat::~ParseThat()
{
}

bool ParseThat::setup_args(std::vector<std::string> &pt_args)
{
	pt_args.push_back(std::string("-i"));
	pt_args.push_back(utos((unsigned) inst_level_));
	pt_args.push_back(std::string("-p"));
	pt_args.push_back(utos((unsigned) parse_level));
	pt_args.push_back(std::string("-v ") + utos(verbosity));

	if (include_libs_) 
		pt_args.push_back(std::string("--include-libs"));
	
	if (merge_tramps) 
		pt_args.push_back(std::string("--merge-tramps"));

	if (rewrite_filename.length()) 
		pt_args.push_back(std::string("--binary-edit=") + rewrite_filename);

	if (do_recursive) 
		pt_args.push_back(std::string("-r"));

	if (print_summary_) 
		pt_args.push_back(std::string("--summary"));

	if (timeout_secs) 
		pt_args.push_back(std::string("-t ") + utos(timeout_secs));

	if (do_trace) 
		pt_args.push_back(std::string("-T ") + utos(tracelength));

	if (suppress_ipc) 
		pt_args.push_back(std::string("--suppress-ipc"));

	if (skip_mods.length()) 
		pt_args.push_back(std::string("--skip-mod=") + skip_mods);

	if (skip_funcs.length()) 
		pt_args.push_back(std::string("--skip-func=") + skip_funcs);

	if (limit_mod.length()) 
		pt_args.push_back(std::string("--only-mod=") + limit_mod);

	if (limit_func.length()) 
		pt_args.push_back(std::string("--only-func=") + limit_func);

	if (pt_out_name.length()) 
		pt_args.push_back(std::string("-o ") + pt_out_name);

	if (trans != T_None)
	{
		std::string tstr = std::string("--use-transactions=");

		switch(trans) 
		{
			case T_Func: tstr += std::string("func"); break;
			case T_Mod: tstr += std::string("mod"); break;
			case T_Proc: tstr += std::string("proc"); break;
			default: tstr += std::string("invalid"); break;
		};

		pt_args.push_back(tstr);
	}

	return true;
}

test_results_t ParseThat::pt_execute(std::vector<std::string> &pt_args)
{

#if defined (os_windows_test)
	
	logerror("%s[%d]:  skipping parseThat test for this platform for now\n", 
			FILE__, __LINE__);
	return SKIPPED;
	
#else

	if (!pt_path.length()) pt_path = std::string("parseThat");

	char cmdbuf[2048];
	sprintf(cmdbuf, "%s", pt_path.c_str());
	logerror("%s[%d]:  parseThat: %s\n", FILE__, __LINE__, pt_path.c_str());

	for (unsigned int i = 0; i < pt_args.size(); ++i)
	{
		sprintf(cmdbuf, "%s %s", cmdbuf, pt_args[i].c_str());
	}

	logerror("%s[%d]:  about to issue parseThat command: \n\t\t'%s'\n", 
			FILE__, __LINE__, cmdbuf);

	int res = system(cmdbuf);

	if (WIFEXITED(res))
	{
		short status = WEXITSTATUS(res);
		if (0 != status)
		{
			logerror("%s[%d]:  parseThat cmd failed with code %d\n", 
					FILE__, __LINE__, status);
			return FAILED;
		}
	}
	else
	{
		logerror("%s[%d]:  parseThat cmd failed\n", FILE__, __LINE__);
		if (WIFSIGNALED(res))
		{
			logerror("%s[%d]:  received signal %d\n", FILE__, __LINE__, WTERMSIG(res));
		}
		return FAILED;
	}

	return PASSED;
#endif
}

test_results_t ParseThat::operator()(std::string exec_path, std::vector<std::string> &mutatee_args)
{
	
	struct stat statbuf;
	int result = stat(BINEDIT_DIR, &statbuf);
	if (-1 == result)
	{
		result = mkdir(BINEDIT_DIR, 0700);
		if (result == -1) {
			logerror("%s[%d]: Could not mkdir %s: %s\n ", FILE__, __LINE__, BINEDIT_DIR,strerror(errno) );
			return FAILED;
		}
	}

	std::vector<std::string> pt_args;
	if (!setup_args(pt_args))
	{
		logerror("%s[%d]:  failed to setup parseThat args\n", FILE__, __LINE__);
		return FAILED;
	}

	//  maybe want to check existence of mutatee executable here?

	pt_args.push_back(exec_path);
	for (unsigned int i = 0; i < mutatee_args.size(); ++i)
	{
		pt_args.push_back(mutatee_args[i]);
	}

	if (cmd_stdout_name.length() && cmd_stdout_name == cmd_stderr_name)
	{
		//  both to same file
		pt_args.push_back(std::string("&>") + cmd_stdout_name);
	}
	else
	{
		if (cmd_stdout_name.length())
		{
			pt_args.push_back(std::string("1>") + cmd_stdout_name);
		}
		if (cmd_stderr_name.length())
		{
			pt_args.push_back(std::string("2>") + cmd_stderr_name);
		}
	}

	return pt_execute(pt_args);
}

test_results_t ParseThat::operator()(int pid)
{
	std::vector<std::string> pt_args;
	if (!setup_args(pt_args))
	{
		logerror("%s[%d]:  failed to setup parseThat args\n", FILE__, __LINE__);
		return FAILED;
	}

	pt_args.push_back(std::string("--pid=") + itos(pid));

	if (cmd_stdout_name.length() && cmd_stdout_name == cmd_stderr_name)
	{
		//  both to same file
		pt_args.push_back(std::string("&>") + cmd_stdout_name);
	}
	else
	{
		if (cmd_stdout_name.length())
		{
			pt_args.push_back(std::string("1>") + cmd_stdout_name);
		}
		if (cmd_stderr_name.length())
		{
			pt_args.push_back(std::string("2>") + cmd_stderr_name);
		}
	}

	return pt_execute(pt_args);
}