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
?>

<?php if (!empty($content['hero'])): ?>
  <div<?php print drupal_attributes($region_attributes_array['hero'])?>>
    <?php print $content['hero'] ?>
  </div>
<?php endif; ?>


<?php if (!empty($content['mainContent'])): ?>
  <div class="layout l-container">
    <?php foreach($content['mainContent'] as $name => $item): ?>
      <?php if (!empty($item)): ?>
        <div<?php print drupal_attributes($region_attributes_array[$name])?>>
          <?php print $item ?>
        </div>
      <?php endif; ?>
    <?php endforeach; ?>
  </div>
<?php endif; ?>

<?php if (!empty($content['bottom'])): ?>
  <div<?php print drupal_attributes($region_attributes_array['bottom'])?>>
    <div class="bg-none">
      <?php print $content['bottom'] ?>
    </div>
  </div>
<?php endif; ?>
