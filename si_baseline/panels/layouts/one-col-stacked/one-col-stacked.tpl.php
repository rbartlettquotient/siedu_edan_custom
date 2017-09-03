<?php
/**
 * @file
 * Template for the Omega Grid 3 layout.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
//dpm($variables);
?>
<?php foreach($content as $name => $item): ?>
  <?php if (!empty($item)): ?>
    <div<?php print drupal_attributes($region_attributes_array[$name])?>>
      <?php print $item ?>
    </div>
  <?php endif; ?>
<?php endforeach; ?>
