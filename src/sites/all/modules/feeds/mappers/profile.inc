<?php
// $Id: profile.inc,v 1.1 2010/06/19 15:32:07 alexb Exp $

/**
 * @file
 * On behalf implementation of Feeds mapping API for user profiles.
 */

/**
 * Implementation of feeds_user_processor_target_alter().
 */
function profile_feeds_user_processor_targets_alter(&$targets) {
  if (module_exists('profile')) {
    $categories = profile_categories();

    foreach ($categories as $category) {
      $result = _profile_get_fields($category['name']);
      while ($record = db_fetch_object($result)) {
        $targets[$record->name] = array(
          'name' => t('Profile:'. $record->title),
          'description' => t('Profile:'. $record->title),
          'callback' => 'profile_feeds_set_target',
        );
      }
    }
  }
}

/**
 * Set the user profile target after import.
 */
function profile_feeds_set_target($account, $target, $value) {
  $account->{$target} = $value;
  return $account;
}
