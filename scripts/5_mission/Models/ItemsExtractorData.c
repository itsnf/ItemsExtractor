class ItemsExtractorData 
{
    private ref array<ref array<string>> Rows;

    void ItemsExtractorData() 
    {
        Rows = new array<ref array<string>>;
    }

    void AddRow(string row) 
    {
        ref array<string> rowArray = ParseRow(row);
        Rows.Insert(rowArray);
    }

    private array<string> ParseRow(string row, string separator = ":") 
    {
        array<string> result = new array<string>;
        row.Split(separator, result);
        return result;
    }

    void WriteToCSV(string path = "$profile:\\ItemsExtractor\\ItemsExtractorData.csv")
    {
        CheckAndCreateDirectories(path);
        
        FileHandle file = OpenFile(path, FileMode.WRITE);

        if (file != 0) 
        {
            array<string> FileData = {
                "Number,Item Type,Item Localized Name,Item Localization Key"
            };

            for (int i = 0; i < Rows.Count(); i++)
            {
                string rowValue = (1 + i).ToString() + ",";
                for (int j = 0; j < Rows[i].Count(); j++)
                {
                    rowValue += Rows[i][j] + ",";
                }
                FileData.Insert(rowValue);
            }

            foreach(string row: FileData)
            {
                FPrintln(file, row);
            }

            CloseFile(file);
            ErrorEx("Items data saved to " + path, ErrorExSeverity.INFO);
        } 
        else 
        {
            ErrorEx("Unable to create " + path + " file.", ErrorExSeverity.ERROR);
        }
    }

    private void CheckAndCreateDirectories(string path) 
    {
        array<string> folders = new array<string>;
        path.Replace("/", "\\");
        path.Split("\\", folders);

        string currentPath = "";
        for (int i = 0; i < folders.Count(); i++) 
        {
            if (i > 0) {
                currentPath += "\\" + folders[i];
            } else {
                currentPath = folders[i];
            }

            if (i < folders.Count() - 1) 
            {
                if (!FileExist(currentPath)) 
                {
                    MakeDirectory(currentPath);
                }
            } 
            else 
            {
                FileHandle file = OpenFile(currentPath, FileMode.WRITE);
                if (file != 0) 
                {
                    CloseFile(file);
                }
            }
        }
    }
};
