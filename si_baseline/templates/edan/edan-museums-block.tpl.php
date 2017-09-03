
<div class="edan-records edan-records-block edan-records-museum">
<?php
$i = 0;
foreach($content as $record_id => $record):
//dpm($record); // this will show all of the available records and their fields
$title = array_key_exists('unit', $record) ? $record['unit'] : '';

$logo_html = '';
$img_src = array_key_exists('image', $record) ? $record['image'] : '';
if(strlen($img_src) > 0) {
  $img_html = '<img src="' . $img_src . '" alt="' . $title . ' icon" />';
}
//$museum_link = l($title, '/museum/' . $record_id);
//$link = url('/museum/' . $record_id);
$museum_link = l($title, $record['local_path']);
$i++;
?>
  <?php /*?><?php if ($i == 1 || $i % 3 == 0): ?>
    <div class="row">
  <?php endif; ?><?php */?>
  <div class="edan-record edan-record-museum record-<?php print $record_id ?>">
  <div class="museum-record">
    <a href="<?php print $record['local_path']; ?>">
      <span class="museum-icon icon"><?php echo $img_html; ?></span>
      <span class="museum-title"><?php echo($title); ?></span>
    </a>
  </div>
</div>
<?php /*?><?php if ($i % 4 == 0): ?>
    </div>
  <?php endif; ?><?php */?>
<?php endforeach; ?>
</div>