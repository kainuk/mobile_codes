<?php
/**
 * @file
 * Variable module integration.
 */

/**
 * Implements hook_variable_info().
 */
function mobile_codes_variable_info() {
  $variable = array();

  $variable['mobile_codes_settings'] = array(
    'title' => t('Mobile Codes settings'),
    'type' => 'mobile_codes_settings',
    'default' => mobile_codes_defaults(),
    'access' => 'administer mobile codes',
    'group' => 'mobile_codes',
  );

  return $variable;
}

/**
 * Implements hook_variable_type_info().
 */
function mobile_codes_variable_type_info() {
  $type = array();

  $type['mobile_codes_settings'] = array(
    'title' => t('Mobile Codes settings'),
    'element callback' => 'mobile_codes_variable_element_mobile_codes_settings',
  );

  return $type;
}

/**
 * Implements hook_variable_group_info().
 */
function mobile_codes_variable_group_info() {
  $groups['mobile_codes'] = array(
    'title' => t('Mobile Codes'),
    'description' => t('Mobile Codes configuration settings'),
    'access' => 'administer mobile codes',
    'path' => array('admin/config/content/mobile_codes'),
  );
  return $groups;
}

/**
 * Element callback for Mobile Ocdes settings variable type.
 */
function mobile_codes_variable_element_mobile_codes_settings($variable, $options = array()) {
  $form = $form_state = array();

  module_load_include('admin.inc', 'mobile_codes');
  $form = mobile_codes_settings_form($form, $form_state);

  $form['settings']['#tree'] = TRUE;
  return $form['settings'];
}
