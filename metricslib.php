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

$mainFile = 'simple.cpp';
$lang =  getProgrammingLanguage($mainFile);

$metrics = getAllAvailableMetrics($lang);
var_dump($metrics);

system("dump.sh " . $mainFile . "_DUMP_.xml", $retval);

?>