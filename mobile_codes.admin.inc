<?php
/**
 * @file
 * Administration functions for the Mobile Codes module.
 */

/**
 * Settings form callback.
 */
function mobile_codes_settings_form($form, &$form_state) {
  $form['#tree'] = TRUE;

  $defaults = mobile_codes_defaults();

  $settings = array();
  drupal_alter('mobile_codes_settings', $settings);
  foreach ($settings as $type => $setting) {
    $form['settings'][$type] = array(
      '#type' => 'fieldset',
      '#title' => t('@type settings', array('@type' => drupal_strtoupper($type))),
    );

    $order = array();
    if (is_array($settings[$type]) && count($settings[$type]) > 0) {
      foreach ($settings[$type] as $setting => $values) {
        $weight = isset($values['weight']) ? $values['weight'] : 0;
        $order[$weight] = isset($order[$weight]) ? $order[$weight] : array();
        $order[$weight][] = $setting;
      }

      ksort($order);
      foreach ($order as $order_settings) {
        sort($order_settings);
        foreach ($order_settings as $setting) {
          $form['settings'][$type][$setting] = array(
            '#type' => 'checkbox',
            '#title' => check_plain($settings[$type][$setting]['label']),
            '#description' => check_plain($settings[$type][$setting]['description']),
            '#default_value' => isset($defaults[$type][$setting]) ? $defaults[$type][$setting] : FALSE,
          );
          if (isset($settings[$type][$setting]['form']) && is_array($settings[$type][$setting]['form'])) {
            $form['settings'][$type][$setting] = $settings[$type][$setting]['form'] + $form['settings'][$type][$setting];
          }
        }
      }
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

/**
 * Submit callback for Mobile Codes settings form.
 */
function mobile_codes_settings_form_submit($form, &$form_state) {
  drupal_set_message(t('Mobile Codes settings have been updated.'));
  variable_set('mobile_codes_settings', $form_state['values']['settings']);
}
