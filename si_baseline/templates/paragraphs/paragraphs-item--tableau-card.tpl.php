<?php

/**
 * @file
 * Default theme implementation for a single paragraph item.
 *
 * Available variables:
 * - $content: An array of content items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity
 *   - entity-paragraphs-item
 *   - paragraphs-item-{bundle}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
//dpm($variables);
$entity = $elements['#entity'];
$group = $elements['#fieldgroups']['group_info'];
$classes .= isset($field_column_two) ? ' layout' : '';
$title = $content['field_section_title'];
hide($content['field_section_title']);
if (isset($content['field_column_two'])) {
  $column_two = $content['field_column_two'];
  hide($content['field_column_two']);
}

?>

<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($content['field_section_title']); ?>
  <div class="first col-md-7">
    <?php print $tableau_numbers; ?>
    <?php print render($content); ?>
  </div>
  <?php if (isset($content['field_column_two'])): ?>
    <div class="col-md-5 col-md last">
      <?php print render($content['field_column_two']); ?>
    </div>
  <?php endif; ?>
</div>
