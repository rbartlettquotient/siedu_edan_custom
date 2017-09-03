<?php 

/**
 * Implements hook_preprocess_panels_pane().
 */
function si_baseline_preprocess_panels_pane(&$vars) {
  $type = $vars['pane']->type;
  $type_class = drupal_html_class($type);
  $subtype = $vars['pane']->subtype;
  $subtype_class = drupal_html_class($subtype);
  $layout = $vars['display']->layout;
  $only_use_smacss = theme_get_setting('only_use_smacss');

  // Add theme hook suggestions based on pane type and layout.
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $layout;
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $subtype;
  $vars['theme_hook_suggestions'][] = 'panels_pane__' . $layout . '__' . $subtype;

  // Add id to the attributes array.
//  if (isset($vars['pane']->css['css_id'])) {
//    $vars['attributes_array']['id'] = $vars['pane']->css['css_id'];
//  }
  if($vars['pane']->type == 'node_title') {
    $vars['node'] = isset($vars['display']->context['requiredcontext_entity:node_1']) ? $vars['display']->context['requiredcontext_entity:node_1']->data : $vars['display']->context['argument_entity_id:node_1']->data;
//    dpm($vars['node']);
  }
 // dpm($vars);
}
