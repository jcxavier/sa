<?php
require_once('metricsconstants.php');

function getProgrammingLanguage($filename)
{
    global $progExt;
    
    $pos = strrpos($filename, ".");
    
    if ($pos === false) 
        return NULL;
    
    $ext = substr($filename, $pos + 1);
    
    if (isset($progExt[$ext]))
        return $progExt[$ext];
        
    return NULL;
}

function getAllAvailableMetrics($lang)
{
    global $metrics;
    
    return $metrics[$lang];
}

function dumpFile($src, $dump)
{
    system(DUMP_SCRIPT . " " . $src . " " . $dump);
}

function setMetrics(/* TODO */)
{
    /*
    $exec[HALSTEAD]['difficultyLevel'] =        0;
    $exec[HALSTEAD]['effortToImplement'] =      0;
    $exec[HALSTEAD]['numberDeliveredBugs'] =    0;
    $exec[HALSTEAD]['numberUniqueOperands'] =   0;
    $exec[HALSTEAD]['numberUniqueOperators'] =  0;
    $exec[HALSTEAD]['programLength'] =          0;
    $exec[HALSTEAD]['timeToImplement'] =        0;
    $exec[HALSTEAD]['totalNumberOperands'] =    0;
    $exec[HALSTEAD]['totalNumberOperators'] =   0;
    $exec[HALSTEAD]['vocabularySize'] =         0;
    
    $exec[STYLE]['blockBracketsSingle'] =       0;
    $exec[STYLE]['checkTabs'] =                 0;
    $exec[STYLE]['programLineSize'] =           0;
    $exec[STYLE]['spaceBracketsCode'] =         0;
    $exec[STYLE]['spaceCommentsText'] =         0;
    $exec[STYLE]['spaceParentesisBrackets'] =   0;
    
    $exec[MISC]['cyclomaticComplexity'] =       0;
    $exec[MISC]['linesOfCode'] =                0;
    */
    
    $exec[HALSTEAD]['numberUniqueOperands'] =   0;
    $exec[HALSTEAD]['numberUniqueOperators'] =  0;
    $exec[HALSTEAD]['programLength'] =          0;
    $exec[HALSTEAD]['timeToImplement'] =        0;
    
    $exec[STYLE]['programLineSize'] =           0;
    $exec[STYLE]['spaceBracketsCode'] =         0;
    $exec[STYLE]['spaceCommentsText'] =         0;
    
    $exec[MISC]['cyclomaticComplexity'] =       0;
    
    return $exec;
}

function executeAllMetrics($metrics, $src, $srcNC, $dump)
{
    return executeMetrics($metrics, $metrics, $src, $srcNC, $dump);
}

function executeMetrics($metrics, $exec, $src, $srcNC, $dump)
{ 
    if (isset($exec[HALSTEAD]))
        foreach ($exec[HALSTEAD] as $metric => $val)
        {        
            $path = METRICS_PATH . $metrics[HALSTEAD][$metric] . " " . $srcNC . " " . $dump;
            $exec[HALSTEAD][$metric] = system($path);
        }
    
    if (isset($exec[STYLE]))
        foreach ($exec[STYLE] as $metric => $val)
        {        
            $path = METRICS_PATH . $metrics[STYLE][$metric] . " " . $srcNC;
            $exec[STYLE][$metric] = system($path);
        }
        
    if (isset($exec[MISC]))
    {
       $exec[MISC]['cyclomaticComplexity'] =
           system(METRICS_PATH . $metrics[MISC]['cyclomaticComplexity'] . " " . $dump);
     
       $exec[MISC]['linesOfCode'] = system(METRICS_PATH . $metrics[MISC]['linesOfCode'] . " " . $src);
    }
     
    return $exec;
}

if ($argc != 3)
    die("usage: php " . $argv[0] . " <source code file> <xml dump file>\n");

$src =      $argv[1];
$srcNC =    NC_PREFIX . $argv[1];
$dump =     $argv[2];

if (!file_exists($src))
    die("Fatal error: source code file " . $src . " was not found\n");

// if either the source file without comments or the dump file was not found, generate them    
if (!file_exists($srcNC) || !file_exists($dump))
    dumpFile($src, $dump);

$lang =  getProgrammingLanguage($src);
$metrics = getAllAvailableMetrics($lang);

$exec = setMetrics();

//$metrics = executeMetrics($metrics, $exec, $src, $srcNC, $dump);
$metrics = executeAllMetrics($metrics, $src, $srcNC, $dump);
var_dump($metrics);



?>