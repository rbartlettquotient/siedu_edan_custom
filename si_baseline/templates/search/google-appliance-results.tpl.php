<?php
// $Id$
/**
 * @file 
 *    default theme implementation for displaying Google Search Appliance results
 *
 * This template collects each invocation of theme_google_appliance_result(). This and
 * the child template are dependent on one another sharing the markup for the 
 * results listing
 *
 * @see template_preprocess_google_appliance_results()
 * @see template_preprocess_google_appliance_result()
 * @see google-appliance-result.tpl.php
 */
//dsm($variables);
?>

<div class="search-results-wrapper">

  <?php if (!empty($spelling_suggestion)): ?>
    <?php print $spelling_suggestion; ?>
  <?php endif; ?>
  
 <?php if (isset($show_synonyms) && $show_synonyms) : ?>
  <div class="synonyms google-appliance-synonyms">
    <span class="p"><?php print $synonyms_label ?></span> <ul><?php print $synonyms; ?></ul>
  </div>
 <?php endif; ?>

<?php if (!isset($response_data['error'])) : ?>


  <?php if (!empty($keymatch_results)) : ?>
    <ol class="keymatch-results google-appliance-keymatch-results">
      <?php print $keymatch_results; ?>
    </ol>
  <?php endif; ?>
  <div id="site-search" class="search-results-container">
  <ul class="search-results reset-list google-appliance-results search-list">
    <?php print $search_results; ?>
  </ul>

    <div id="placeholder"></div>
  <?php print $pager; ?>
    </div>

<?php else : ?>
  <p><?php print $error_reason ?></p>
<?php endif; ?>
</div>