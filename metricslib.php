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

function executeMetrics($metrics, $exec)
{
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
    
    $exec[MISC]['cyclomaticComplexity'] = system("./metrics/" . $metrics[MISC]['cyclomaticComplexity'] . " _DUMP_.xml");
    $exec[MISC]['linesOfCode'] = system("./metrics/" . $metrics[MISC]['linesOfCode'] . " simple.cpp");
    
    
    foreach (array_keys($exec[HALSTEAD]) as $metric)
    {        
        $path = "./metrics/" . $metrics[HALSTEAD][$metric] . " _nc_simple.cpp _DUMP_.xml";
        $exec[HALSTEAD][$metric] = system($path);
    }
    
    foreach (array_keys($exec[STYLE]) as $metric)
    {        
        $path = "./metrics/" . $metrics[STYLE][$metric] . " _nc_simple.cpp";
        $exec[STYLE][$metric] = system($path);
    }
     
    var_dump($exec);
}

$mainFile = 'simple.cpp';
$lang =  getProgrammingLanguage($mainFile);

$metrics = getAllAvailableMetrics($lang);
var_dump($metrics);

executeMetrics($metrics, array());

//system("./dump.sh " . $mainFile . " _DUMP_.xml", $retval);

?>