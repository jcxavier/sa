<?php
/**
 * Library of constants to be used by the static analysis library.
 * This file exists merely to separate the functions from the constants.
 */

// String constants
define('VERBOSE_EXT', 'Verbose');
define('HALSTEAD', 'halstead');
define('STYLE', 'style');
define('MISC', 'misc');

// List of defined metrics by programming language
$metrics['C'] =         array("halstead" => array(), "style" => array(), );
$metrics['C++'] =       array("halstead" => array(), "style" => array(), );
$metrics['Java'] =      array();
$metrics['Scheme'] =    array();
$metrics['SQL'] =       array();

// Map of programming language extensions to programming language names
$progExt = array(
    'c' => 'C',
    'cpp' => 'C++',
    'java' => 'Java',
    'scm' => 'Scheme',
    'sql' => 'SQL'
);

// Halstead Software Science
$halstead['difficultyLevel'] =          '/halstead/difficultyLevel.sh';
$halstead['effortToImplement'] =        '/halstead/effortToImplement.sh';
$halstead['numberDeliveredBugs'] =      '/halstead/numberDeliveredBugs.sh';
$halstead['numberUniqueOperands'] =     '/halstead/numberUniqueOperands.sh';
$halstead['numberUniqueOperators'] =    '/halstead/numberUniqueOperators.sh';
$halstead['programLength'] =            '/halstead/programLength.sh';
$halstead['programLevel'] =             '/halstead/programLevel.sh';
$halstead['timeToImplement'] =          '/halstead/timeToImplement.sh';
$halstead['totalNumberOperands'] =      '/halstead/totalNumberOperands.sh';
$halstead['totalNumberOperators'] =     '/halstead/totalNumberOperators.sh';
$halstead['vocabularySize'] =           '/halstead/vocabularySize.sh';

// Style metrics as defined by Submit!
$style['blockBracketsSingle'] =         '/style/blockBracketsSingle.sh';
$style['checkTabs'] =                   '/style/checkTabs.sh';
$style['programLineSize'] =             '/style/blockBracketsSingle.sh';
$style['spaceBracketsCode'] =           '/style/blockBracketsSingle.sh';
$style['spaceCommentsText'] =           '/style/blockBracketsSingle.sh';
$style['spaceParentesisBrackets'] =     '/style/blockBracketsSingle.sh';

// Other metrics
$misc['cyclomaticComplexity'] =         'cyclomaticComplexity.sh';
$misc['linesOfCode'] =                  'linesOfCode.sh';


// Mapping of metrics to programming languages
// C
$metrics['C']['HALSTEAD'] =     $halstead;
$metrics['C']['STYLE'] =        $style;
$metrics['C']['MISC'] =         $misc;

// C++
$metrics['C++']['HALSTEAD'] =   $halstead;
$metrics['C++']['STYLE'] =      $style;
$metrics['C++']['MISC'] =       $misc;

// Java

// Scheme

// SQL

?>