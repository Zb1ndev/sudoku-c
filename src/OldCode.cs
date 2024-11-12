public string SeedGenerator(List<KeyValuePair<string, int>> tile) {

    // Sort Rows
    for (int i = 0; i < 9; i++)
    {
        // Basically if (i+1 % 3 != 0)
        if ((i + 1) != 3 && (i + 1) != 6 && (i + 1) != 9)
        {
            // Honestly no clue why this runs twice, though I dont feel like looking at it very hard
            for (int k = 0; k < 2; k++)
            {

                // Get Current Row
                List<string> CurrentRow = new List<string>();
                foreach (KeyValuePair<string, int> kv in tile)
                {
                    if (kv.Key[1] == (i + 1).ToString()[0])
                    {
                        CurrentRow.Add(kv.Key);
                    }
                }

                // Get Rows Under 
                List<string> RowsBelow = new List<string>();
                for (int g = 0; g < 2; g++)
                {
                    foreach (KeyValuePair<string, int> kv in tile)
                    {
                        if (kv.Key[1] == ((i + 1) + (g + 1)).ToString()[0])
                        {
                            RowsBelow.Add(kv.Key);
                        }
                    }
                }

                // Get Duplicates
                int counter = 0;
                List<string> Originals = new List<string>();
                List<string> Duplicates = new List<string>();
                foreach (string Tile in CurrentRow)
                {
                    counter++;
                    int offset = 0;
                    foreach (string uTile in CurrentRow)
                    {
                        if (offset >= counter)
                        {
                            if (tiles[uTile] == tiles[Tile])
                            {
                                Originals.Add(Tile);
                                Duplicates.Add(uTile);
                                break;
                            }
                        }
                        offset++;
                    }
                }

                // Get a list of values not in row
                List<int> OldValues = new List<int>();
                List<int> Values = new List<int>(); // List of values not in row
                foreach (string Tile in CurrentRow)
                {
                    OldValues.Add(tiles[Tile]);
                }
                foreach (char c in n)
                {
                    if (!OldValues.Contains(Int32.Parse(c.ToString())))
                    {
                        Values.Add(Int32.Parse(c.ToString()));
                    }
                }

                int dCounter = 0;
                foreach (string dupe in Duplicates)
                {
                    int pass = 0;
                    foreach (string Tile in RowsBelow)
                    {
                        if (Tile[0] == dupe[0] && Values.Contains(tiles[Tile]))
                        {
                            Values.Remove(tiles[Tile]);
                            SwapValues(dupe, Tile);
                            break;
                        }
                        else
                        {
                            pass++;
                        }
                    }
                    if (pass == RowsBelow.Count)
                    {
                        string currentTile = Originals[dCounter];
                        foreach (string Tile in RowsBelow)
                        {
                            if (Tile[0] == currentTile[0] && Values.Contains(tiles[Tile]))
                            {
                                Values.Remove(tiles[Tile]);
                                SwapValues(currentTile, Tile);
                                break;
                            }
                        }
                    }
                    dCounter++;
                }

            }
        }
    }

    // Sort Columns
    for (int i = 0; i < 9; i++)
    {
        if ((i + 1) != 3 && (i + 1) != 6 && (i + 1) != 9)
        {
            List<string> tried = new List<string>();
            for (int k = 0; k < 9; k++)
            {

                // Get Current Columns
                List<string> CurrentColumn = new List<string>();
                foreach (KeyValuePair<string, int> kv in tile)
                {
                    if (kv.Key[2] == (i + 1).ToString()[0])
                    {
                        CurrentColumn.Add(kv.Key);
                    }
                }

                // Get Columns to the Right 
                List<string> ColumnsBelow = new List<string>();
                for (int g = 0; g < 2; g++)
                {
                    foreach (KeyValuePair<string, int> kv in tile)
                    {
                        if (kv.Key[2] == ((i + 1) + (g + 1)).ToString()[0])
                        {
                            ColumnsBelow.Add(kv.Key);
                        }
                    }
                }

                // Get Duplicates
                int counter = -1;
                List<string> Originals = new List<string>();
                List<string> Duplicates = new List<string>();
                foreach (string Tile in CurrentColumn)
                {
                    counter++;
                    int offset = -1;
                    foreach (string uTile in CurrentColumn)
                    {
                        if (offset >= counter)
                        {
                            if (tiles[uTile] == tiles[Tile])
                            {
                                Originals.Add(Tile);
                                Duplicates.Add(uTile);
                                break;
                            }
                        }
                        offset++;
                    }
                }

                // Get a list of values not in column
                List<int> OldValues = new List<int>();
                List<int> Values = new List<int>(); // List of values not in row
                foreach (string Tile in CurrentColumn)
                {
                    OldValues.Add(tiles[Tile]);
                }
                foreach (char c in n)
                {
                    if (!OldValues.Contains(Int32.Parse(c.ToString())))
                    {
                        Values.Add(Int32.Parse(c.ToString()));
                    }
                }

                // Swap Numbers
                int runCounter = 0;
                // First Check
                foreach (string dupe in Duplicates)
                {
                    int pass = 0;
                    foreach (string uTile in ColumnsBelow)
                    {
                        if (uTile[0] == dupe[0] && uTile[1] == dupe[1])
                        {
                            if (Values.Contains(tiles[uTile]))
                            {
                                pass++;
                                SwapValues(uTile, dupe);
                                break;
                            }
                        }
                    }
                    // First Redundant Check
                    if (pass == 0)
                    {
                        foreach (string uTile in ColumnsBelow)
                        {
                            if (uTile[0] == Originals[runCounter][0] && uTile[1] == Originals[runCounter][1])
                            {
                                if (Values.Contains(tiles[uTile]))
                                {
                                    pass++;
                                    SwapValues(uTile, Originals[runCounter]);
                                    break;
                                }
                            }
                        }
                    }

                    // This is an old check list I guess I never completed
                    /// Look for a tile in current column that has the value in its row and group - X
                    /// check if any available duplicates have that tiles value
                    /// if so then make the duplicate swap with that value and make the random tile swap with the value we need

                    // Second Redundant Check
                    if (pass == 0)
                    {
                        // Get Tile with value in its row and column
                        bool hasDuplicate = false;
                        string duplicate = "";
                        string vTile = "", kTile = ""; // vTile : the tile that contains the value, kTile : the tile with the vTile in its row and group
                        int x = 0;

                        foreach (string uTile in CurrentColumn)
                        {
                            if (!tried.Contains(uTile))
                            {
                                foreach (string bTile in ColumnsBelow)
                                {
                                    if (Values.Contains(tiles[bTile]) && bTile[0] == uTile[0] && bTile[1] == uTile[1] && x == 0)
                                    {
                                        x++;
                                        vTile = bTile;
                                        kTile = uTile;
                                        break;
                                    }
                                }
                            }
                        }

                        foreach (string uTile in CurrentColumn)
                        {
                            if (uTile != kTile && tiles[kTile] == tiles[uTile])
                            {
                                hasDuplicate = true;
                                duplicate = uTile;
                            }
                        }

                        if (hasDuplicate)
                        {
                            SwapValues(duplicate, vTile);
                        }
                        else
                        {
                            SwapValues(kTile, vTile);
                            tried.Add(kTile);
                        }

                    }
                    runCounter++;
                }

            }
        }
    }

    // Writes the seed to a string lol
    // Write Seed to Readable Format
    foreach (KeyValuePair<string, int> key in tile) {
        seed = seed + tiles[key.Key].ToString();
    }

    return seed;

}

/* 
        I think this was an attempt later on to make the code more readable ( Hence the different curly braces convention ). 
        So all the generator code use to be just one function. I also dont think the stop watch works as it reads 1ms sometimes
        and I dont think I was that good at programming.
*/
public string GenerateSeed() {

    Stopwatch watch = new Stopwatch();
    watch.Start();

    string newSeed = "";
    List<KeyValuePair<string, int>> tile = tiles.ToList();
    List<int> duplicates = new List<int>();
    int check = 0;
    string group = "abcdefghi";
        
    bool usableSeed = false;
    while (!usableSeed) {

        SeedGenerator(tile);

        check = 0;
        foreach (char g in group) {
            duplicates = new List<int>();
            foreach (KeyValuePair<string, int> kv in tile) {
                if (kv.Key[0] == g) {
                    if (!duplicates.Contains(tiles[kv.Key])) {
                        duplicates.Add(tiles[kv.Key]);
                        check++;
                    }
                    else {
                        break;
                    }
                }
            }
        }

        if (check == 81) usableSeed = true;

    }

    watch.Stop();
    generationTime = watch.ElapsedMilliseconds;

    // Write Seed to Readable Format
    foreach (KeyValuePair<string, int> key in tile)
    {
        newSeed = newSeed + tiles[key.Key].ToString();
    }

    return newSeed;
}

public string FinishSeed(string level)
{
    List<KeyValuePair<string, int>> tile = tiles.ToList();
    int difficulty = 81;
    if (debug)
    {
        if (gm_easy) { difficulty -= rnd.Next(20, 25); }
        if (gm_normal) { difficulty -= rnd.Next(17, 20); }
        if (gm_hard) { difficulty -= rnd.Next(11, 17); }

        for (int i = 0; i < difficulty; i++)
        {
            int randTile = rnd.Next(0, 81);
            tiles[tile[randTile].Key] = 0;
        }

        // Write Seed to Readable Format
        level = "";
        foreach (KeyValuePair<string, int> key in tile)
        {
            level = level + tiles[key.Key].ToString();
            tiles[key.Key] = 0;
        }
    }
    return level;
}
public void SwapValues(string key1, string key2)
{
    int first = 0, second = 0;
    first = tiles[key1];
    second = tiles[key2];

    tiles[key1] = second;
    tiles[key2] = first;
}