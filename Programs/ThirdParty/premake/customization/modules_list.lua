-- Implement the modules_list command for solution-scope files
require('vstudio')

premake.api.register {
	name = "modules_list",
	scope = "workspace",
	kind = "list:string",
}
