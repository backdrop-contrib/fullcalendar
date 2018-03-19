<?php

/**
 * @file
 * Provides extra FullCalendar configuration options for Colorbox.
 */

/**
 * Implements hook_fullcalendar_options_info().
 */
function colorbox_fullcalendar_options_info() {
  return array(
    'colorbox' => array(
      'name' => t('Colorbox'),
      'js' => TRUE,
      'parent' => 'fullcalendar_options',
    ),
  );
}

/**
 * Implements hook_fullcalendar_options_definition().
 */
function colorbox_fullcalendar_options_definition() {
  $options['colorbox']['contains'] = array(
    'colorbox' => array(
      'default' => FALSE,
      'bool' => TRUE,
    ),
    'colorboxIFrame' => array(
      'default' => FALSE,
      'bool' => TRUE,
    ),
    'colorboxClass' => array('default' => '#content'),
    'colorboxWidth' => array('default' => '80%'),
    'colorboxHeight' => array('default' => '80%'),
  );
  return $options;
}

/**
 * Implements hook_fullcalendar_options_form().
 */
function colorbox_fullcalendar_options_form(&$form, &$form_state, &$view) {
  $form['colorbox']['colorbox'] = array(
    '#type' => 'checkbox',
    '#title' => t('Open events with Colorbox'),
    '#default_value' => $view->options['colorbox']['colorbox'],
    '#data_type' => 'bool',
  );
  $form['colorbox']['colorboxIFrame'] = array(
    '#type' => 'checkbox',
    '#title' => t('Open events in iFrame'),
    '#default_value' => $view->options['colorbox']['colorboxIFrame'],
    '#states' => array(
      'visible' => array(
        ':input[name="style_options[colorbox][colorbox]"]' => array('checked' => TRUE),
      ),
    ),
    '#data_type' => 'bool',
  );
  $form['colorbox']['colorboxClass'] = array(
    '#type' => 'textfield',
    '#title' => t('Classname or ID selector'),
    '#default_value' => $view->options['colorbox']['colorboxClass'],
    '#states' => array(
      'visible' => array(
        ':input[name="style_options[colorbox][colorbox]"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['colorbox']['colorboxWidth'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => $view->options['colorbox']['colorboxWidth'],
    '#states' => array(
      'visible' => array(
        ':input[name="style_options[colorbox][colorbox]"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['colorbox']['colorboxHeight'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#default_value' => $view->options['colorbox']['colorboxHeight'],
    '#states' => array(
      'visible' => array(
        ':input[name="style_options[colorbox][colorbox]"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['sameWindow']['#states'] = array(
    'visible' => array(
      ':input[name="style_options[colorbox][colorbox]"]' => array('checked' => FALSE),
    ),
  );
}

/**
 * Implements hook_fullcalendar_options_process().
 */
function colorbox_fullcalendar_options_process(&$variables, &$settings) {
  if (empty($settings['colorbox']['colorbox'])) {
    unset($settings['colorbox']);
  }
}
