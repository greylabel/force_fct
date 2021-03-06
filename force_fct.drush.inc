<?php

/**
 * @file
 * Drush Include for Force FCT Module
 */

define("FORCE_FCT_DEFAULT_LIMIT", 1000);

/**
 * Implements hook_drush_help().
 */
function force_fct_drush_help($command) {
  switch ($command) {
    case 'drush:force-fct':
      return dt('Clears specified number of expired items from cache_form. Defaults to 1000 items.');
  }
}

/**
 * Implements hook_drush_command().
 */
function force_fct_drush_command() {
  $items = array();

  $items['ffct'] = array(
    'description' => dt('Clear a given number of expired form_cache items'),
    'arguments' => array(
      'limit' => dt('Number of entries to delete'),
    ),
    'examples' => array(
      'Standard example' => 'drush force-fct',
      'Argument example' => 'drush force-fct 2500',
    ),
  );

  return $items;
}

/**
 * Callback function for the drush command
 */
function drush_force_fct_ffct($limit = FORCE_FCT_DEFAULT_LIMIT ) {
  _force_fct_delete($limit);
}

/**
 * Remove a given number of expired entries from cache_form
 *
 * @return integer
 *  The number of rows deleted from the cache_form table.
 */
function _force_fct_delete($limit) {
  // Should ideally use placeholders for variables as suggested on https://www.drupal.org/writing-secure-code
  // But drupal db_delete does not support range or orderBy
  if (ctype_digit($limit) && $limit > 1) {    
    db_query("DELETE FROM {cache_form} where expire <> " . CACHE_PERMANENT . " AND expire < " . time() . " ORDER BY expire DESC LIMIT " . $limit);
  }
}
