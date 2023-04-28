enum IEExtractFormats {
    CSV = 1,
    JSON
};

class ItemsExtractor 
{

    private static ref const array<string> PATHS = {
        "CfgVehicles",
        "CfgWeapons",
        "CfgMagazines"
    };

    static void Extract(int ExtractTo = IEExtractFormats.CSV)
    {
        ItemsExtractorData ItemsData = GetItemsData();

        switch (GetGame().ServerConfigGetInt("ItemsExtractorFileType") | ExtractTo)
        {
            case IEExtractFormats.CSV:
                ItemsData.WriteToCSV();
            break;
            case IEExtractFormats.JSON:
                // TODO: ExtractToJSON
            break;

            default:
                ErrorEx("`ExtractTo` parameter does not apply to any format. File was not written.", ErrorExSeverity.WARNING);
            break;
        }
    }

    private static ItemsExtractorData GetItemsData() 
    {
        ItemsExtractorData Result = new ItemsExtractorData;

        foreach(string path: PATHS) 
        {
            int classesCount = GetGame().ConfigGetChildrenCount(path);

            for(int currentClassIdx = 0; currentClassIdx < classesCount; ++currentClassIdx) 
            {
                string className; GetGame().ConfigGetChildName(path, currentClassIdx, className);

                int scope = GetGame().ConfigGetInt(string.Format("%1 %2 scope", path, className));
                
                if (scope == 2) 
                {
                    string itemLocalizedName, rawName; 

                    GetGame().ConfigGetTextRaw(string.Format("%1 %2 displayName", path, className), rawName);

                    if (GetGame().FormatRawConfigStringKeys(rawName)) {
                        itemLocalizedName = Widget.TranslateString(rawName);
                    } else {
                        itemLocalizedName = "<NoData>";
                    }

                    Result.AddRow(string.Format("\"%1\":\"%2\":\"%3\"", className, itemLocalizedName, rawName));
                }
            }
        }

        return Result;
    }
};
