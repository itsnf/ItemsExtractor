# ItemsExtractor

The ItemsExtractor is a script for exporting DayZ game items' data into a specified format. At the moment, only the CSV format is supported. JSON format is currently unavailable.

## Usage

All files will be exported to the following folder: `$profile:\\ItemsExtractor\\ItemsExtractorData.*`. By default, the exported file will be in CSV format.

To change the export format, add a parameter to `ServerDZ.cfg` as follows:

```ini
ItemsExtractorFileType=1;
```

Here, `1` represents CSV format and `2` represents JSON format. If the parameter is not set, the default format will be CSV.

The available formats are:

```csharp
enum IEExtractFormats {
    CSV = 1,
    JSON
};
```

Please note that exporting from scripts is possible, but it is not currently possible to set the export path. Here is the example

```cs
class TestExporting
{
    void TestExporting()
    {
        ItemsExtractor.Extract();
        ItemsExtractor.Extract(IEExtractFormats.JSON);
    }
}

new TestExporting();
```

## Example

Here is the CSV file example represented as a table:

| Number | Item Type | Item Localized Name | Item Localization Key |
|--------|-----------|--------------------|-----------------------|
| 1      | ClassName1| Localized Name1    | Localization Key1     |
| 2      | ClassName2| Localized Name2    | Localization Key2     |
| ...    | ...       | ...                | ...                   |

## Possible Enhancements

In the future, support for JSON format can be added. Moreover, the ability to set custom export paths for the script would be a useful addition.