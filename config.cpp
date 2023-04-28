class CfgMods 
{
	class ItemsExtractor 
	{
		type = "mod";
		class defs 
		{
			class missionScriptModule
			{
				value="";
				files[]= {"ItemsExtractor/scripts/5_Mission"};
			};
		};
	};
};
class CfgPatches 
{
	class ItemsExtractor 
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};