<?php
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * each column roughly equal in width.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['left']: Content in the left column.
 *   - $content['right']: Content in the right column.
 */
//dpm($variables);
$regions = array();
foreach($content as $key => $item) {
  if (!empty($item)) {
    $regions[$key] = $item;
  }
}
$col = count($regions);
?>
<div class="panel-display panel-<?php print $col; ?>col l-container layout" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <?php foreach($regions  as $key => $item): ?>
    <div class="col col--<?php print $key; ?> <?print $col == 2 ? ($key == 'right' ? 'col-sm-6 last' : 'col-sm-6') : 'col-12'; ?>">
      <?php print $item; ?>
    </div>
  <?php endforeach; ?>
</div>
